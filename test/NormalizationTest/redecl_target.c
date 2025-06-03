// TEST: Consecutive Redeclarations - Target
// Normalized code with consecutive redeclarations handled
// Expected: Identical AST after redeclaration normalization

#include <stdio.h>

int main() {
    // Normalized consecutive redeclarations (only keep last/valid one)
    int x;  // Normalized from multiple consecutive declarations
    
    // Normalized redeclarations with values (keep last meaningful assignment)
    int y = 20;  // Normalized from consecutive redeclarations with values
    
    // Redeclarations in different scopes (preserved as they're valid)
    int a = 5;
    {
        int a = 10;  // Valid scope redeclaration preserved
        printf("Inner a: %d\n", a);
    }
    printf("Outer a: %d\n", a);
    
    // Function parameter redeclarations in scopes (preserved)
    int param = 100;
    {
        int param = 200;  // Valid scope shadow preserved
        {
            int param = 300;  // Valid nested scope preserved
            printf("Innermost param: %d\n", param);
        }
        printf("Middle param: %d\n", param);
    }
    printf("Outer param: %d\n", param);
    
    // Array redeclarations normalized
    int arr[5];  // Normalized array declaration
    
    // Pointer redeclarations normalized
    int *ptr;  // Normalized pointer declaration
    
    // Consecutive redeclarations with assignments normalized
    int value;  // Normalized declaration
    value = 42;
    value = 84;  // Assignments preserved
    
    printf("Final values: x=%d, y=%d, value=%d\n", x, y, value);
    return 0;
}

// Function redeclarations normalized (single forward declaration)
void function1();  // Normalized function declaration

void function1() {
    printf("Function implementation\n");
}
