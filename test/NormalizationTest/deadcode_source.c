// TEST: Dead Code Removal - Source
// Tests removal of unreachable code after return statements
// Expected: Should normalize to same AST as deadcode_target.c

#include <stdio.h>

int function_with_dead_code(int x) {
    if (x > 0) {
        printf("Positive number\n");
        return 1;
        // Dead code after return - should be removed
        printf("This will never execute\n");
        x = x * 2;
        int unused_var = 42;
    } else if (x < 0) {
        printf("Negative number\n");
        return -1;
        // More dead code - should be removed
        printf("Also unreachable\n");
        return 999;  // Unreachable return
    } else {
        printf("Zero\n");
        return 0;
        // Dead code in else branch - should be removed
        for (int i = 0; i < 10; i++) {
            printf("Never runs\n");
        }
    }
    
    // Unreachable code after all branches return - should be removed
    printf("This is completely unreachable\n");
    return 99;
}

int another_function(int y) {
    int result = y * 2;
    
    if (y == 0) {
        return 0;
        // Dead code block - should be removed
        {
            int local = 5;
            printf("Dead block\n");
            local++;
        }
    }
    
    printf("Before return\n");
    return result;
    
    // Everything after this return is dead - should be removed
    printf("Dead statement 1\n");
    y++;
    if (y > 100) {
        printf("Dead conditional\n");
        return y;
    }
    printf("Dead statement 2\n");
}

int main() {
    int value = 10;
    int result = function_with_dead_code(value);
    int other = another_function(value);
    
    printf("Results: %d, %d\n", result, other);
    return 0;
    
    // Dead code in main - should be removed
    printf("This won't print\n");
    value = 999;
}
