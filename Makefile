# Makefile for AST-CC Plagiarism Detector
# Use: make (or make all) to build everything
#      make clean to clean build artifacts
#      make detector to build just the main detector

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Iinclude -Ibuild
BISON = bison

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Source files
SOURCES = $(SRC_DIR)/helper.cpp $(SRC_DIR)/lexer.cpp $(SRC_DIR)/plagcheck.cpp
PARSER_SOURCE = $(BUILD_DIR)/parser.cpp
ALL_SOURCES = $(SOURCES) $(PARSER_SOURCE)

# Targets
DETECTOR = $(BIN_DIR)/detector_with_filtering.exe
PARSER = $(BIN_DIR)/c_parser.exe

# Default target
all: $(DETECTOR) $(PARSER)

# Create directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Generate parser from Bison grammar
$(PARSER_SOURCE): $(SRC_DIR)/AST.y | $(BUILD_DIR)
	cd $(SRC_DIR) && $(BISON) -d -v AST.y -o ../$(BUILD_DIR)/parser.cpp

# Build main detector
$(DETECTOR): $(ALL_SOURCES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ALL_SOURCES) -o $@

# Build basic parser
$(PARSER): $(SOURCES) $(PARSER_SOURCE) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -DPARSER_ONLY $(SOURCES) $(PARSER_SOURCE) -o $@

# Individual targets
detector: $(DETECTOR)
parser: $(PARSER)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(BIN_DIR)/*.exe

# Test the detector
test: $(DETECTOR)
	@echo "Running basic test..."
	./$(DETECTOR) test/original.c --ast-cc-test test/similar.c

# Show available targets
help:
	@echo "Available targets:"
	@echo "  all      - Build both detector and parser (default)"
	@echo "  detector - Build main plagiarism detector"
	@echo "  parser   - Build basic parser"
	@echo "  test     - Run a basic test"
	@echo "  clean    - Remove build artifacts"
	@echo "  help     - Show this help message"

.PHONY: all detector parser clean test help
