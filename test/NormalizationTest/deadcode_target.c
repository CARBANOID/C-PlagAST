// TEST: Dead Code Removal - Target
// Code with dead code removed that should match deadcode_source.c after normalization
// Expected: Identical AST after dead code removal

#include <stdio.h>

int function_with_dead_code(int x) {
    if (x > 0) {
        printf("Positive number\n");
        return 1;
        // Dead code removed
    } else if (x < 0) {
        printf("Negative number\n");
        return -1;
        // Dead code removed
    } else {
        printf("Zero\n");
        return 0;
        // Dead code removed
    }
    
    // Unreachable code removed
}

int another_function(int y) {
    int result = y * 2;
    
    if (y == 0) {
        return 0;
        // Dead code block removed
    }
    
    printf("Before return\n");
    return result;
    
    // All dead code after return removed
}

int main() {
    int value = 10;
    int result = function_with_dead_code(value);
    int other = another_function(value);
    
    printf("Results: %d, %d\n", result, other);
    return 0;
    
    // Dead code in main removed
}
