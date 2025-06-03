// TEST: Assignment Pattern Normalization - Source
// Tests normalization of compound assignments and increment/decrement operations
// Expected: Should normalize to same AST as assign_target.c

#include <stdio.h>

int main() {
    int x = 10, y = 5, z = 0;
    int array[5] = {1, 2, 3, 4, 5};
    int i = 0;
    
    // Compound assignment operators (should be normalized)
    x += y;          // x = x + y
    z *= 3;          // z = z * 3
    y -= 2;          // y = y - 2
    x /= 2;          // x = x / 2
    z %= 4;          // z = z % 4
    
    // Increment and decrement operators
    i++;             // i = i + 1
    ++i;             // i = i + 1
    y--;             // y = y - 1
    --y;             // y = y - 1
    
    // Compound assignments with arrays
    array[0] += 10;  // array[0] = array[0] + 10
    array[1] *= 2;   // array[1] = array[1] * 2
    
    // Complex compound assignments
    x += y * z;      // x = x + (y * z)
    z -= array[i++]; // z = z - array[i]; i = i + 1
    
    // Chained assignments (should remain as is)
    int a, b, c;
    a = b = c = 42;
    
    printf("Results: x=%d, y=%d, z=%d, i=%d\n", x, y, z, i);
    return 0;
}
