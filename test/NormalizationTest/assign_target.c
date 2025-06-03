// TEST: Assignment Pattern Normalization - Target
// Expanded assignments that should normalize to same AST as assign_source.c
// Expected: Identical AST after normalization

#include <stdio.h>

int main() {
    int x = 10, y = 5, z = 0;
    int array[5] = {1, 2, 3, 4, 5};
    int i = 0;
    
    // Expanded compound assignments
    x = x + y;       // from x += y
    z = z * 3;       // from z *= 3
    y = y - 2;       // from y -= 2
    x = x / 2;       // from x /= 2
    z = z % 4;       // from z %= 4
    
    // Expanded increment/decrement operations
    i = i + 1;       // from i++
    i = i + 1;       // from ++i
    y = y - 1;       // from y--
    y = y - 1;       // from --y
    
    // Expanded array compound assignments
    array[0] = array[0] + 10;  // from array[0] += 10
    array[1] = array[1] * 2;   // from array[1] *= 2
    
    // Expanded complex compound assignments
    x = x + (y * z);           // from x += y * z
    z = z - array[i];          // from z -= array[i++]
    i = i + 1;                 // continuation from i++
    
    // Chained assignments (should remain as is)
    int a, b, c;
    a = b = c = 42;
    
    printf("Results: x=%d, y=%d, z=%d, i=%d\n", x, y, z, i);
    return 0;
}
