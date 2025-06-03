#!/bin/bash

# AST-CC Plagiarism Detector Build Script
# This script compiles the project using Bison and g++ in WSL

echo "=== AST-CC Plagiarism Detector Build Script ==="
echo "Building C++ plagiarism detection tool with Bison parser..."

# Set up directories
SRC_DIR="src"
INCLUDE_DIR="include"
BIN_DIR="bin"
BUILD_DIR="build"

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"
mkdir -p "$BIN_DIR"

# Step 1: Generate parser from Bison grammar
echo "Step 1: Generating parser from Bison grammar..."
cd "$SRC_DIR"
bison -d -v AST.y -o ../build/parser.cpp
if [ $? -ne 0 ]; then
    echo "Error: Bison parser generation failed!"
    exit 1
fi
echo "✓ Bison parser generated successfully"

# Move header file to build directory
if [ -f "AST.tab.h" ]; then
    mv AST.tab.h ../build/parser.h
fi

cd ..

# Step 2: Compile the project
echo "Step 2: Compiling C++ sources..."

# Compilation flags
CXXFLAGS="-std=c++17 -Wall -Wextra -I$INCLUDE_DIR -I$BUILD_DIR"
SOURCES="$SRC_DIR/helper.cpp $SRC_DIR/lexer.cpp $SRC_DIR/plagcheck.cpp build/parser.cpp"

# Compile the main detector
echo "Compiling detector_with_filtering..."
g++ $CXXFLAGS $SOURCES -o "$BIN_DIR/detector_with_filtering.exe"
if [ $? -ne 0 ]; then
    echo "Error: Compilation failed!"
    exit 1
fi
echo "✓ detector_with_filtering.exe compiled successfully"

# Compile the basic parser (optional)
echo "Compiling c_parser..."
g++ $CXXFLAGS $SRC_DIR/helper.cpp $SRC_DIR/lexer.cpp build/parser.cpp -DPARSER_ONLY -o "$BIN_DIR/c_parser.exe"
if [ $? -ne 0 ]; then
    echo "Warning: c_parser.exe compilation failed, but main detector is ready"
else
    echo "✓ c_parser.exe compiled successfully"
fi

echo ""
echo "=== Build Complete ==="
echo "Executables created in $BIN_DIR/:"
ls -la "$BIN_DIR/"
echo ""
echo "Usage:"
echo "  ./bin/detector_with_filtering.exe original.c --ast-cc-test suspected.c"
echo ""
