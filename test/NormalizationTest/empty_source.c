// TEST: Empty Block Detection - Source
// Tests detection and handling of empty code blocks
// Expected: Should normalize to same AST as empty_target.c

#include <stdio.h>

int main() {
    int x = 10, y = 20;
    
    // Empty if block
    if (x > 0) {
        // Empty block - should be detected and handled
    }
    
    // Empty else block
    if (x < 0) {
        printf("Negative\n");
    } else {
        // Empty else block
    }
    
    // Empty while loop
    int counter = 0;
    while (counter > 10) {
        // Empty loop body
    }
    
    // Empty for loop
    for (int i = 0; i < 0; i++) {
        // Empty for body
    }
    
    // Nested empty blocks
    if (x > 0) {
        if (y > 0) {
            // Nested empty block
        }
    }
    
    // Empty function blocks would be tested separately
    
    // Mixed empty and non-empty blocks
    if (x == 10) {
        printf("x is 10\n");
    } else if (x == 20) {
        // Empty elif block
    } else {
        printf("x is something else\n");
    }
    
    // Empty block with comments only
    if (y == 20) {
        // This is just a comment
        // Another comment
        /* Multi-line comment
           that doesn't contain code */
    }
    
    // Empty switch case
    switch (x) {
        case 10:
            printf("Ten\n");
            break;
        case 20:
            // Empty case
            break;
        default:
            // Empty default
            break;
    }
    
    printf("End of main\n");
    return 0;
}
