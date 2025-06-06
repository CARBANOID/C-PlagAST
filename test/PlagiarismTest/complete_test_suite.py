#!/usr/bin/env python3
"""
AST-CC Plagiarism Detector - Complete Testing Suite
====================================================

This script provides a comprehensive testing interface for the AST-CC Plagiarism Detector.
It includes all analysis types: pairwise comparison, ground truth evaluation, and threshold optimization.

Date: June 6, 2025
"""

import os
import sys
import subprocess
import csv
import time
import platform
import re
from pathlib import Path

def find_project_root():
    """
    Dynamically find the project root directory by looking for key files
    """
    current_dir = Path(__file__).parent.absolute()
    
    # Look for project indicators going up the directory tree
    indicators = ['detector_with_filtering.exe', 'AST.y', 'Makefile', 'build.bat']
    
    # Start from current directory and go up
    search_dir = current_dir
    for _ in range(10):  # Limit search to 10 levels up
        # Check if we found the project root
        bin_dir = search_dir / 'bin'
        src_dir = search_dir / 'src'
        
        if (bin_dir.exists() and 
            (bin_dir / 'detector_with_filtering.exe').exists() and
            src_dir.exists() and 
            (src_dir / 'AST.y').exists()):
            return search_dir
            
        # Go up one level
        parent = search_dir.parent
        if parent == search_dir:  # Reached filesystem root
            break
        search_dir = parent
    
    # Fallback: try to find based on common patterns
    home_dir = Path.home()
    common_paths = [
        home_dir / 'CODING' / 'PROJECTS' / 'PBL' / 'Compiler',
        home_dir / 'Projects' / 'AST_CC_Plagiarism_Detector',
        home_dir / 'AST_CC_Plagiarism_Detector',
        Path('/mnt/c/Users') / os.getenv('USERNAME', 'user') / 'CODING' / 'PROJECTS' / 'PBL' / 'Compiler',
    ]
    
    for base_path in common_paths:
        if base_path.exists():
            # Look for AST_CC_Plagiarism_Detector directory
            for item in base_path.rglob('AST_CC_Plagiarism_Detector'):
                if item.is_dir():
                    bin_dir = item / 'bin'
                    if (bin_dir.exists() and 
                        (bin_dir / 'detector_with_filtering.exe').exists()):
                        return item
    
    raise FileNotFoundError("Could not find AST_CC_Plagiarism_Detector project root directory")

def convert_path_for_environment(path, env):
    """
    Convert path format based on environment
    """
    path_str = str(path)
    
    if env == 'windows':
        # Ensure Windows format
        if path_str.startswith('/mnt/'):
            # Convert WSL path to Windows path
            # /mnt/c/... -> C:\...
            drive_letter = path_str[5].upper()
            windows_path = path_str[6:].replace('/', '\\')
            return f"{drive_letter}:{windows_path}"
        return path_str.replace('/', '\\')
    else:
        # WSL/Linux format
        if ':' in path_str and len(path_str) > 1 and path_str[1] == ':':
            # Convert Windows path to WSL path
            # C:\... -> /mnt/c/...
            drive_letter = path_str[0].lower()
            wsl_path = path_str[2:].replace('\\', '/')
            return f"/mnt/{drive_letter}{wsl_path}"
        return path_str.replace('\\', '/')

def detect_environment():
    """
    Detect if we're running in Windows or WSL
    Returns: 'windows', 'wsl', or 'linux'
    """
    system = platform.system().lower()
    
    if system == 'windows':
        return 'windows'
    elif system == 'linux':
        # Check if we're in WSL
        try:
            with open('/proc/version', 'r') as f:
                version_info = f.read().lower()
                if 'microsoft' in version_info or 'wsl' in version_info:
                    return 'wsl'
                else:
                    return 'linux'
        except:
            return 'linux'
    else:
        return 'unknown'

class PlagiarismTestSuite:
    def __init__(self, test_dir=None):
        if test_dir is None:
            self.test_dir = Path(__file__).parent
        else:
            self.test_dir = Path(test_dir)
        
        # Detect environment and get dynamic paths
        self.env = detect_environment()
        
        try:
            self.project_root = find_project_root()
            self.detector_path = self.project_root / "bin" / "detector_with_filtering.exe"
        except FileNotFoundError as e:
            print(f"❌ Error finding project paths: {e}")
            print("Please ensure you're running this script from within the AST_CC_Plagiarism_Detector project")
            sys.exit(1)
        
        self.c_files = list(self.test_dir.glob("*.c"))
        
        print(f"🔍 AST-CC Plagiarism Detector Test Suite")
        print(f"🌐 Detected environment: {self.env.upper()}")
        print(f"📂 Test Directory: {self.test_dir}")
        print(f"🏗️ Project Root: {self.project_root}")
        print(f"🔧 Detector Path: {self.detector_path}")
        print(f"📄 Found {len(self.c_files)} C files for testing")
        print("=" * 80)
    
    def run_pairwise_analysis(self, output_file="pairwise_analysis_results.csv"):
        """Run complete pairwise analysis on all C files"""
        print("🚀 Running Pairwise Analysis...")
        
        results = []
        total_pairs = len(self.c_files) * (len(self.c_files) - 1) // 2
        current_pair = 0
        
        with open(self.test_dir / output_file, 'w', newline='', encoding='utf-8') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(['file1', 'file2', 'similarity', 'status', 'details'])
            
            for i, file1 in enumerate(self.c_files):
                for j, file2 in enumerate(self.c_files[i+1:], i+1):
                    current_pair += 1
                    print(f"📊 Progress: {current_pair}/{total_pairs} - Comparing {file1.name} vs {file2.name}")
                    
                    try:
                        # Run plagiarism detection with cross-platform command
                        if self.env == 'windows':
                            # Windows: Use WSL to run the detector
                            wsl_detector = convert_path_for_environment(self.detector_path, 'wsl')
                            wsl_test_dir = convert_path_for_environment(self.test_dir, 'wsl')
                            file1_wsl = f"{wsl_test_dir}/{file1.name}"
                            file2_wsl = f"{wsl_test_dir}/{file2.name}"
                            cmd = ["wsl", wsl_detector, file1_wsl, "--ast-cc-test", file2_wsl]
                        else:
                            # WSL/Linux: Run detector directly
                            detector_native = convert_path_for_environment(self.detector_path, self.env)
                            cmd = [detector_native, file1.name, "--ast-cc-test", file2.name]
                        
                        result = subprocess.run(cmd, capture_output=True, text=True, 
                                              encoding='utf-8', errors='replace', timeout=30, cwd=str(self.test_dir))
                        
                        if result.returncode == 0:
                            # Parse similarity from output using improved regex
                            similarity = self.parse_similarity_from_output(result.stdout)
                            
                            row = [file1.name, file2.name, similarity, "SUCCESS", "Analysis completed"]
                            results.append(row)
                            writer.writerow(row)
                        else:
                            row = [file1.name, file2.name, 0.0, "ERROR", f"Return code: {result.returncode}, stderr: {result.stderr[:100]}"]
                            results.append(row)
                            writer.writerow(row)
                    
                    except subprocess.TimeoutExpired:
                        row = [file1.name, file2.name, 0.0, "TIMEOUT", "Analysis timed out"]
                        results.append(row)
                        writer.writerow(row)
                    except Exception as e:
                        row = [file1.name, file2.name, 0.0, "EXCEPTION", str(e)]
                        results.append(row)
                        writer.writerow(row)
        
        print(f"✅ Pairwise analysis completed! Results saved to {output_file}")
        return results
      
    def run_ground_truth_analysis(self, input_file="pairwise_analysis_results.csv", threshold=50.0):
        """Run ground truth analysis with confusion matrix"""
        print(f"🎯 Running Ground Truth Analysis (Threshold: {threshold}%)...")
        
        # Load ground truth mapping from CSV file
        ground_truth_pairs = self.load_ground_truth_from_csv()
        if not ground_truth_pairs:
            print("❌ Failed to load ground truth data. Cannot proceed with analysis.")
            return None
            
        # Load pairwise results
        if not (self.test_dir / input_file).exists():
            print(f"❌ Input file {input_file} not found. Running pairwise analysis first...")
            self.run_pairwise_analysis(input_file)
        
        results = []
        tp = fp = tn = fn = 0
        
        with open(self.test_dir / input_file, 'r', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                file1, file2 = row['file1'], row['file2']
                try:
                    similarity = float(row['similarity'])
                except (ValueError, KeyError):
                    print(f"⚠️ Warning: Could not parse similarity for {file1} vs {file2}, using 0.0")
                    similarity = 0.0
                
                # Determine ground truth
                is_plagiarism = self.is_plagiarism_pair(file1, file2, ground_truth_pairs)
                predicted_plagiarism = similarity >= threshold
                
                # Classification
                if is_plagiarism and predicted_plagiarism:
                    classification = "TP"
                    tp += 1
                elif is_plagiarism and not predicted_plagiarism:
                    classification = "FN"
                    fn += 1
                elif not is_plagiarism and predicted_plagiarism:
                    classification = "FP"
                    fp += 1
                else:
                    classification = "TN"
                    tn += 1
                
                results.append({
                    'file1': file1,
                    'file2': file2,
                    'ground_truth': is_plagiarism,
                    'predicted': predicted_plagiarism,
                    'similarity': similarity,
                    'status': row['status'],
                    'classification': classification
                })
        
        # Calculate metrics
        precision = tp / (tp + fp) if (tp + fp) > 0 else 0
        recall = tp / (tp + fn) if (tp + fn) > 0 else 0
        f1_score = 2 * precision * recall / (precision + recall) if (precision + recall) > 0 else 0
        accuracy = (tp + tn) / (tp + tn + fp + fn)
        
        # Display results
        print(f"\n📊 CONFUSION MATRIX (Threshold: {threshold}%):")
        print("┌─────────────────┬─────────────────────────────┐")
        print("│                 │         Predicted           │")
        print("├─────────────────┼──────────────┬──────────────┤")
        print("│                 │  Plagiarism  │ Not Plagiarism│")
        print("├─────────────────┼──────────────┼──────────────┤")
        print(f"│    Plagiarism   │     {tp:3d}      │      {fn:3d}     │")
        print("│ Actual          ├──────────────┼──────────────┤")
        print(f"│ Not Plagiarism  │     {fp:3d}      │     {tn:3d}     │")
        print("└─────────────────┴──────────────┴──────────────┘")
        
        print(f"\n📊 PERFORMANCE METRICS:")
        print(f"   Precision: {precision:.3f} ({tp}/{tp + fp})")
        print(f"   Recall:    {recall:.3f} ({tp}/{tp + fn})")
        print(f"   F1-Score:  {f1_score:.3f}")
        print(f"   Accuracy:  {accuracy:.3f} ({tp + tn}/{tp + tn + fp + fn})")
        
        # Save detailed results
        output_file = f"ground_truth_analysis_threshold_{int(threshold)}.csv"
        with open(self.test_dir / output_file, 'w', newline='', encoding='utf-8') as csvfile:
            fieldnames = ['file1', 'file2', 'ground_truth', 'predicted', 'similarity', 'status', 'classification']
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(results)
        
        print(f"💾 Detailed results saved to: {output_file}")
        return {'tp': tp, 'fp': fp, 'tn': tn, 'fn': fn, 'precision': precision, 'recall': recall, 'f1_score': f1_score, 'accuracy': accuracy}
    
    def run_threshold_optimization(self, input_file="pairwise_analysis_results.csv", thresholds=None):
        """Run analysis across multiple thresholds to find optimal performance"""
        if thresholds is None:
            thresholds = [30, 40, 50, 60, 70, 80]
        
        print("🔧 Running Threshold Optimization...")
        print("=" * 60)
        print(f"{'Threshold':<10} {'Precision':<10} {'Recall':<8} {'F1-Score':<9} {'Accuracy':<9}")
        print("-" * 60)
        
        best_f1 = 0
        best_threshold = 50
        results = []
        
        for threshold in thresholds:
            metrics = self.run_ground_truth_analysis(input_file, threshold)
            results.append({**{'threshold': threshold}, **metrics})
            
            print(f"{threshold}%{'':<8} {metrics['precision']:<10.3f} {metrics['recall']:<8.3f} {metrics['f1_score']:<9.3f} {metrics['accuracy']:<9.3f}")
            
            if metrics['f1_score'] > best_f1:
                best_f1 = metrics['f1_score']
                best_threshold = threshold
        
        print("=" * 60)
        print(f"🏆 OPTIMAL THRESHOLD: {best_threshold}% (F1-Score: {best_f1:.3f})")
        
        return results, best_threshold
    
    def is_plagiarism_pair(self, file1, file2, ground_truth_pairs):
        """Check if a file pair represents plagiarism using ground truth data"""
        pair1 = (file1, file2)
        pair2 = (file2, file1)
        
        # Check both orderings in the ground truth mapping
        if pair1 in ground_truth_pairs:
            return ground_truth_pairs[pair1]
        elif pair2 in ground_truth_pairs:
            return ground_truth_pairs[pair2]
        else:
            # If pair not found in ground truth, log warning and assume no plagiarism
            print(f"⚠️ Warning: Pair ({file1}, {file2}) not found in ground truth mapping. Assuming no plagiarism.")
            return False
    
    def run_complete_analysis(self):
        """Run the complete testing suite"""
        print("🚀 STARTING COMPLETE AST-CC PLAGIARISM DETECTOR ANALYSIS")
        print("=" * 80)
        
        start_time = time.time()
        
        # Step 1: Pairwise Analysis
        print("\n🔍 STEP 1: PAIRWISE SIMILARITY ANALYSIS")
        pairwise_results = self.run_pairwise_analysis("complete_pairwise_results.csv")
        
        # Step 2: Threshold Optimization
        print("\n🔧 STEP 2: THRESHOLD OPTIMIZATION")
        threshold_results, best_threshold = self.run_threshold_optimization("complete_pairwise_results.csv")
        
        # Step 3: Final Analysis with Best Threshold
        print(f"\n🎯 STEP 3: FINAL ANALYSIS WITH OPTIMAL THRESHOLD ({best_threshold}%)")
        final_metrics = self.run_ground_truth_analysis("complete_pairwise_results.csv", best_threshold)
        
        end_time = time.time()
        duration = end_time - start_time
        
        print("\n" + "=" * 80)
        print("✅ COMPLETE ANALYSIS FINISHED!")
        print(f"⏱️  Total Duration: {duration:.2f} seconds")
        print(f"🏆 Best Threshold: {best_threshold}% (F1-Score: {final_metrics['f1_score']:.3f})")
        print(f"📊 Final Accuracy: {final_metrics['accuracy']:.3f}")
        print("📄 All results saved to respective CSV files")
        print("📋 See FINAL_PLAGIARISM_TESTING_REPORT.md for detailed analysis")
        
        return {
            'pairwise_results': pairwise_results,
            'threshold_results': threshold_results,
            'best_threshold': best_threshold,
            'final_metrics': final_metrics,
            'duration': duration
        }
    
    def load_ground_truth_from_csv(self, ground_truth_file="ground_truth.csv"):
        """Load ground truth plagiarism relationships from CSV file
        
        Expected CSV format: file1,file2,actual_label,reasoning
        where actual_label is 1 (plagiarized) or 0 (not plagiarized)
        """
        ground_truth_path = self.test_dir / ground_truth_file
        
        if not ground_truth_path.exists():
            print(f"❌ Ground truth file {ground_truth_file} not found!")
            print("📝 Please create a ground truth file with format: file1,file2,actual_label,reasoning")
            return {}
        
        ground_truth_pairs = {}
        
        try:
            with open(ground_truth_path, 'r', encoding='utf-8') as csvfile:
                reader = csv.DictReader(csvfile)
                for row in reader:
                    file1 = row['file1'].strip()
                    file2 = row['file2'].strip()
                    actual_label = int(row['actual_label'].strip())
                    
                    # Convert to boolean (1 = True, 0 = False)
                    is_plagiarism = bool(actual_label)
                    
                    # Store both orderings for easy lookup
                    ground_truth_pairs[(file1, file2)] = is_plagiarism
                    ground_truth_pairs[(file2, file1)] = is_plagiarism
            
            print(f"✅ Loaded {len(ground_truth_pairs) // 2} ground truth relationships from {ground_truth_file}")
            
            # Count plagiarism vs non-plagiarism cases
            plagiarism_count = sum(1 for v in ground_truth_pairs.values() if v) // 2
            non_plagiarism_count = sum(1 for v in ground_truth_pairs.values() if not v) // 2
            print(f"📊 Ground truth contains: {plagiarism_count} plagiarism pairs, {non_plagiarism_count} non-plagiarism pairs")
            
            return ground_truth_pairs
            
        except Exception as e:
            print(f"❌ Error loading ground truth file: {e}")
            return {}
    
    def parse_similarity_from_output(self, output):
        """
        Parse similarity score from detector output using multiple patterns
        """
        if not output:
            return 0.0
        
        # Try multiple patterns to extract similarity
        for line in output.split('\n'):
            # Pattern 1: "AST-CC Similarity score: 75%"
            if 'AST-CC Similarity score:' in line:
                match = re.search(r'(\d+\.?\d*)%', line)
                if match:
                    return float(match.group(1))
            
            # Pattern 2: "Similarity: 75%" or "similarity: 75%"
            if 'Similarity:' in line or 'similarity:' in line.lower():
                match = re.search(r'(\d+\.?\d*)%', line)
                if match:
                    return float(match.group(1))
            
            # Pattern 3: Any percentage in similarity-related line
            if 'similarity' in line.lower():
                match = re.search(r'(\d+\.?\d*)%', line)
                if match:
                    return float(match.group(1))
        
        # If no explicit similarity found, look for other indicators
        if "identical" in output.lower() or "100%" in output:
            return 100.0
        
        # Look for fraction format like "45/45 nodes"
        match = re.search(r'(\d+)/(\d+)', output)
        if match:
            numerator = float(match.group(1))
            denominator = float(match.group(2))
            if denominator > 0:
                return (numerator / denominator) * 100
        
        return 0.0


def main():
    """Main function to run the test suite"""
    if len(sys.argv) > 1:
        test_dir = sys.argv[1]
    else:
        test_dir = None
    
    suite = PlagiarismTestSuite(test_dir)
    
    print("\nChoose analysis type:")
    print("1. Complete Analysis (All steps)")
    print("2. Pairwise Analysis Only")
    print("3. Ground Truth Analysis (requires existing pairwise results)")
    print("4. Threshold Optimization")
    print("5. Quick Test (50% threshold)")
    
    try:
        choice = input("\nEnter your choice (1-5): ").strip()
        
        if choice == '1':
            suite.run_complete_analysis()
        elif choice == '2':
            suite.run_pairwise_analysis()
        elif choice == '3':
            threshold = float(input("Enter threshold (default 50%): ") or "50")
            suite.run_ground_truth_analysis(threshold=threshold)
        elif choice == '4':
            suite.run_threshold_optimization()
        elif choice == '5':
            suite.run_ground_truth_analysis("comprehensive_analysis_results.csv", 50.0)
        else:
            print("Invalid choice. Running complete analysis...")
            suite.run_complete_analysis()
            
    except KeyboardInterrupt:
        print("\n\n⚠️ Analysis interrupted by user")
    except Exception as e:
        print(f"\n❌ Error occurred: {e}")


if __name__ == "__main__":
    main()
