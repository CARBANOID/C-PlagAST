#!/usr/bin/env python3
"""
WSL AST-CC Normalization Test Runner
Tests normalization effectiveness using the WSL-compiled detector
"""

import subprocess
import os
import re
from pathlib import Path

def run_ast_cc_test_wsl(source_file, target_file):
    """
    Run AST-CC test using WSL and return similarity score
    """
    try:
        # Convert Windows paths to WSL paths
        source_wsl = f"/mnt/d/CODING/PROJECTS/PBL/Compiler/Project2_Backup/AST_CC_Plagiarism_Detector/test/NormalizationTest/{source_file}"
        target_wsl = f"/mnt/d/CODING/PROJECTS/PBL/Compiler/Project2_Backup/AST_CC_Plagiarism_Detector/test/NormalizationTest/{target_file}"
        detector_wsl = "/mnt/d/CODING/PROJECTS/PBL/Compiler/Project2_Backup/AST_CC_Plagiarism_Detector/bin/detector_with_filtering.exe"
        
        # Run the command through WSL
        cmd = ["wsl", detector_wsl, source_wsl, "--ast-cc-test", target_wsl]
        
        result = subprocess.run(
            cmd,
            capture_output=True,
            text=True,
            encoding='utf-8',
            errors='ignore',
            timeout=30
        )
        
        if result.returncode == 0:
            output = result.stdout
            # Parse the output to extract similarity score
            for line in output.split('\n'):
                if 'Similarity:' in line or 'similarity' in line.lower():
                    # Extract percentage
                    match = re.search(r'(\d+\.?\d*)%', line)
                    if match:
                        return float(match.group(1))
                    # Extract decimal value
                    match = re.search(r'(\d+\.?\d+)', line)
                    if match:
                        val = float(match.group(1))
                        return val * 100 if val <= 1.0 else val
            
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
            
            # If we have output but no clear similarity, return 0
            return 0.0
        else:
            print(f"Command failed with return code {result.returncode}")
            print(f"Error output: {result.stderr}")
            return None
            
    except subprocess.TimeoutExpired:
        print("❌ Test timed out")
        return None
    except Exception as e:
        print(f"Exception running AST-CC test: {e}")
        return None

def main():
    print("=== WSL AST-CC Normalization Test Runner ===")
    print("Testing normalization effectiveness using WSL-compiled detector")
    print("=" * 50)
      # Define test pairs (only existing files after cleanup)
    test_pairs = [
        ("assign_simple_source.c", "assign_simple_target.c", "Simple Assignment Normalization"),
        ("assign_source.c", "assign_target.c", "Complex Assignment Normalization"),
        ("var_decl_source.c", "var_decl_target.c", "Variable Declaration Normalization"),
        ("deadcode_source.c", "deadcode_target.c", "Dead Code Removal"),
        ("redecl_source.c", "redecl_target.c", "Consecutive Redeclarations"),
        ("expr_source.c", "expr_target.c", "Expression Normalization"),
        ("list_source.c", "list_target.c", "List Structure Normalization"),
        ("literal_source.c", "literal_target.c", "Literal Normalization"),
        ("complex_source.c", "complex_target.c", "Complex Pattern Normalization"),
        ("empty_source.c", "empty_target.c", "Empty File Normalization"),
    ]
    
    results = []
    total_tests = 0
    successful_tests = 0
    high_similarity_count = 0
    similarity_scores = []
    
    for source, target, description in test_pairs:
        if os.path.exists(source) and os.path.exists(target):
            print(f"\nTesting: {description}")
            print(f"Source: {source}")
            print(f"Target: {target}")
            
            similarity = run_ast_cc_test_wsl(source, target)
            total_tests += 1
            
            if similarity is not None:
                successful_tests += 1
                similarity_scores.append(similarity)
                
                if similarity >= 80:
                    high_similarity_count += 1
                    status = "✅ EXCELLENT"
                elif similarity >= 60:
                    status = "⚠️ GOOD"
                else:
                    status = "❌ LOW"
                
                print(f"Similarity: {similarity:.2f}% {status}")
                results.append((description, similarity))
            else:
                print("❌ Failed to get similarity score")
                results.append((description, "ERROR"))
        else:
            print(f"\n⚠️ Skipping {description}: Files not found")
            if not os.path.exists(source):
                print(f"   Missing: {source}")
            if not os.path.exists(target):
                print(f"   Missing: {target}")
    
    # Print summary
    print("\n" + "=" * 60)
    print("NORMALIZATION TEST SUMMARY")
    print("=" * 60)
    print(f"Total test pairs: {total_tests}")
    print(f"Successful tests: {successful_tests}")
    print(f"High similarity (≥80%): {high_similarity_count}")
    
    if successful_tests > 0:
        normalization_effectiveness = (high_similarity_count / successful_tests) * 100
        print(f"Normalization effectiveness: {normalization_effectiveness:.1f}%")
    
    print("\nDetailed Results:")
    print("-" * 60)
    for description, similarity in results:
        if isinstance(similarity, float):
            print(f"{description:<40} {similarity:>6.2f}%")
        else:
            print(f"{description:<40} {similarity:>8}")
    
    # Performance statistics
    if similarity_scores:
        print("\n" + "=" * 60)
        print("PERFORMANCE EVALUATION")
        print("=" * 60)
        avg_similarity = sum(similarity_scores) / len(similarity_scores)
        min_similarity = min(similarity_scores)
        max_similarity = max(similarity_scores)
        
        print(f"Average similarity: {avg_similarity:.2f}%")
        print(f"Minimum similarity: {min_similarity:.2f}%")
        print(f"Maximum similarity: {max_similarity:.2f}%")
        
        if avg_similarity >= 90:
            assessment = "✅ EXCELLENT - Normalization is highly effective"
        elif avg_similarity >= 70:
            assessment = "⚠️ GOOD - Normalization is working well"
        else:
            assessment = "❌ POOR - Normalization needs improvement"
        
        print(f"Overall Assessment: {assessment}")
    
    print("=" * 60)

if __name__ == "__main__":
    main()
