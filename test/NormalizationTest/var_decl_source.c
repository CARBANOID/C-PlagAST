// TEST: Variable Declaration Normalization - Source
// Tests splitting of multi-variable declarations into individual declarations
// Expected: Should normalize to same AST as var_decl_target.c

#include <stdio.h>

int main() {
    // Multi-variable declarations (should be split)
    int a, b, c;
    int x = 10, y = 20, z = 30;
    
    // Mixed initialization patterns
    int i, j = 5, k;
    double pi = 3.14, e, golden = 1.618;
    
    // Complex multi-declarations
    int *ptr1, *ptr2, value;
    char buffer[100], temp, *str_ptr;
    
    // Arithmetic operations using variables
    a = x + y;
    b = j * 2;
    c = (int)(pi * golden);
    
    // Array operations
    for (i = 0; i < 10; i++) {
        buffer[i] = 'A' + i;
    }
    
    printf("Sum: %d\n", a + b + c);
    return 0;
}
