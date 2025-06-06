#!/usr/bin/env python3
"""
Cross-Platform AST-CC Normalization Test Runner
Automatically detects environment (Windows/WSL) and runs tests accordingly
"""

import subprocess
import os
import re
import platform
import sys
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

def get_paths_for_environment(env):
    """
    Get appropriate paths based on environment using dynamic detection
    """
    try:
        project_root = find_project_root()
        detector_path = project_root / 'bin' / 'detector_with_filtering.exe'
        test_dir = project_root / 'test' / 'NormalizationTest'
        
        if env == 'windows':
            return {
                'detector': str(detector_path),
                'test_dir': str(test_dir),
                'wsl_detector': convert_path_for_environment(detector_path, 'wsl'),
                'wsl_test_dir': convert_path_for_environment(test_dir, 'wsl')
            }
        else:  # wsl or linux
            return {
                'detector': convert_path_for_environment(detector_path, env),
                'test_dir': convert_path_for_environment(test_dir, env)
            }
    except FileNotFoundError as e:
        print(f"❌ Error finding project paths: {e}")
        print("Please ensure you're running this script from within the AST_CC_Plagiarism_Detector project")
        sys.exit(1)

def run_ast_cc_test_cross_platform(source_file, target_file, env, paths):
    """
    Run AST-CC test based on detected environment and return similarity score
    """
    try:
        if env == 'windows':
            # Windows: Use WSL to run the detector
            source_wsl = f"{paths['wsl_test_dir']}/{source_file}"
            target_wsl = f"{paths['wsl_test_dir']}/{target_file}"
            detector_wsl = paths['wsl_detector']
            
            cmd = ["wsl", detector_wsl, source_wsl, "--ast-cc-test", target_wsl]
        else:
            # WSL/Linux: Run detector directly
            detector_path = paths['detector']
            cmd = [detector_path, source_file, "--ast-cc-test", target_file]
        
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
            print(f"Command: {' '.join(cmd)}")
            return None
            
    except subprocess.TimeoutExpired:
        print("❌ Test timed out")
        return None
    except Exception as e:
        print(f"Exception running AST-CC test: {e}")
        return None

def main():
    # Detect environment
    env = detect_environment()
    
    print(f"=== Cross-Platform AST-CC Normalization Test Runner ===")
    print(f"Detected environment: {env.upper()}")
    print(f"Script location: {Path(__file__).parent.absolute()}")
    
    # Get paths dynamically
    try:
        paths = get_paths_for_environment(env)
        project_root = find_project_root()
        print(f"Project root: {project_root}")
    except Exception as e:
        print(f"❌ Failed to detect project paths: {e}")
        return
    
    print(f"Testing normalization effectiveness")
    print("=" * 60)
    
    # Change to appropriate test directory
    test_dir = paths['test_dir']
    try:
        os.chdir(test_dir)
        print(f"Working directory: {os.getcwd()}")
    except OSError as e:
        print(f"❌ Failed to change to test directory: {e}")
        print(f"Attempted path: {test_dir}")
        return
    
    # Define test pairs
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
            
            similarity = run_ast_cc_test_cross_platform(source, target, env, paths)
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
    print(f"Environment: {env.upper()}")
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
