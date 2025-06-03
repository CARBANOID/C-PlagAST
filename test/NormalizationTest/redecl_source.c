// TEST: Consecutive Redeclarations - Source
// Tests handling of consecutive variable redeclarations
// Expected: Should normalize to same AST as redecl_target.c

#include <stdio.h>

int main() {
    // Consecutive redeclarations of same variable
    int x;
    int x;  // Redeclaration - should be normalized
    int x;  // Another redeclaration - should be normalized
    
    // Redeclarations with different initial values
    int y = 10;
    int y = 20;  // Redeclaration with new value
    int y;       // Redeclaration without value
    
    // Mixed type redeclarations (technically invalid but testing parser)
    int z;
    // int z;  // Would cause compiler error, so commenting out
    
    // Redeclarations in different scopes
    int a = 5;
    {
        int a = 10;  // Valid redeclaration in inner scope
        printf("Inner a: %d\n", a);
    }
    printf("Outer a: %d\n", a);
    
    // Function parameter redeclarations in inner scopes
    int param = 100;
    {
        int param = 200;  // Shadows outer param
        {
            int param = 300;  // Shadows middle param
            printf("Innermost param: %d\n", param);
        }
        printf("Middle param: %d\n", param);
    }
    printf("Outer param: %d\n", param);
    
    // Array redeclarations
    int arr[5];
    // int arr[10];  // Would cause error, so testing conceptually
    
    // Pointer redeclarations
    int *ptr;
    int *ptr;  // Redeclaration of pointer
    
    // Consecutive redeclarations with assignments
    int value;
    value = 42;
    int value;  // Redeclaration after assignment
    value = 84;
    
    printf("Final values: x=%d, y=%d, value=%d\n", x, y, value);
    return 0;
}

// Function redeclarations (forward declarations)
void function1();
void function1();  // Redeclaration of function prototype

void function1() {
    printf("Function implementation\n");
}
