@echo off
REM Windows batch file to build AST-CC Plagiarism Detector using WSL

echo === AST-CC Plagiarism Detector Build (Windows to WSL) ===
echo.

REM Check if WSL is available
wsl --list --quiet >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: WSL is not available or not properly configured
    echo Please install WSL and a Linux distribution first
    pause
    exit /b 1
)

echo Building project using WSL Ubuntu...
echo.

REM Convert Windows path to WSL path and run build script
wsl bash -c "cd /mnt/d/CODING/PROJECTS/PBL/Compiler/Project2_Backup/AST_CC_Plagiarism_Detector && chmod +x build.sh && ./build.sh"

if %errorlevel% equ 0 (
    echo.
    echo === Build Successful ===
    echo You can now use the executables in the bin/ directory
    echo.
    echo Example usage:
    echo   .\bin\detector_with_filtering.exe test\original.c --ast-cc-test test\similar.c
    echo.
) else (
    echo.
    echo === Build Failed ===
    echo Check the error messages above for details
    echo.
)

pause
