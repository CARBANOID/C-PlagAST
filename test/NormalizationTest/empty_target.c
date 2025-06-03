// TEST: Empty Block Detection - Target
// Normalized code with empty blocks handled appropriately
// Expected: Identical AST after empty block normalization

#include <stdio.h>

int main() {
    int x = 10, y = 20;
    
    // Empty if block - normalized (could be removed or marked)
    if (x > 0) {
        // Empty block normalized
    }
    
    // Empty else block - normalized
    if (x < 0) {
        printf("Negative\n");
    } else {
        // Empty else normalized
    }
    
    // Empty while loop - normalized
    int counter = 0;
    while (counter > 10) {
        // Empty loop normalized
    }
    
    // Empty for loop - normalized
    for (int i = 0; i < 0; i++) {
        // Empty for normalized
    }
    
    // Nested empty blocks - normalized
    if (x > 0) {
        if (y > 0) {
            // Nested empty normalized
        }
    }
    
    // Mixed empty and non-empty blocks - only empty parts normalized
    if (x == 10) {
        printf("x is 10\n");
    } else if (x == 20) {
        // Empty elif normalized
    } else {
        printf("x is something else\n");
    }
    
    // Empty block with comments - normalized
    if (y == 20) {
        // Comments don't affect empty block detection
    }
    
    // Empty switch cases - normalized
    switch (x) {
        case 10:
            printf("Ten\n");
            break;
        case 20:
            // Empty case normalized
            break;
        default:
            // Empty default normalized
            break;
    }
    
    printf("End of main\n");
    return 0;
}
