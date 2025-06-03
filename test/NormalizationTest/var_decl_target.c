// TEST: Variable Declaration Normalization - Target
// Individual variable declarations that should normalize to same AST as var_decl_source.c
// Expected: Identical AST after normalization

#include <stdio.h>

int main() {
    // Individual variable declarations (equivalent to split multi-declarations)
    int a;
    int b;
    int c;
    int x;
    int y;
    int z;
    x = 10;
    y = 20;
    z = 30;
    
    // Individual declarations with separate initializations
    int i;
    int j;
    int k;
    j = 5;
    double pi;
    double e;
    double golden;
    pi = 3.14;
    golden = 1.618;
    
    // Individual pointer and array declarations
    int *ptr1;
    int *ptr2;
    int value;
    char buffer[100];
    char temp;
    char *str_ptr;
    
    // Same arithmetic operations
    a = x + y;
    b = j * 2;
    c = (int)(pi * golden);
    
    // Same array operations
    for (i = 0; i < 10; i++) {
        buffer[i] = 'A' + i;
    }
    
    printf("Sum: %d\n", a + b + c);
    return 0;
}
