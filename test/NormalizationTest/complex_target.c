// TEST: Complex Normalization Scenarios - Expected Target
// Fully normalized version of complex_source.c
// Expected: Identical AST after all normalizations applied

#include <stdio.h>

// Complex function with all normalizations applied
int complex_function(int a, int b, int c) {
    // Normalized variable declarations (split multi-declarations)
    int x;
    int y;
    int z;
    y = a + b;
    int result1;
    int result2;
    int result3;
    result2 = 0;
    
    // Canonicalized expressions and expanded compound assignments
    result1 = (a + b) * c + (a + b) * c;  // Canonicalized to consistent order
    result2 = result2 + y * 2;            // Expanded compound assignment
    result3 = z = x = 42;                 // Chained assignment preserved
    
    // Control flow with dead code removed
    if (a > 0) {
        return result1 + result2;
        // Dead code removed
    } else if (b > 0) {
        x = x + 10;                       // Expanded compound assignment
        return x * result2;
        // Dead code removed
    }
    
    // Empty blocks handled
    if (c == 0) {
        // Empty block normalized
    } else {
        printf("Non-empty else\n");
    }
    
    // Normalized literal representations
    int hex_value = 255;               // Normalized from 0xFF
    int octal_value = 511;             // Normalized from 0777
    double scientific = 150.0;         // Normalized from 1.5e2
    
    // Canonicalized nested expressions
    return (a * b + a * b) + (hex_value + octal_value) - (int)scientific;
}

// Function with redeclarations normalized
void redeclaration_complexity() {
    int var;                        // Normalized consecutive declarations
    var = 10;
    
    {
        int var = 20;              // Valid scope redeclaration preserved
        {
            int var;               // Normalized consecutive declarations
            var = 30;
        }
    }
    
    // Normalized array and pointer declarations
    int array[5];
    int *ptr;
    int value;
    array[0] = array[1] = array[2] = 100;  // Chained assignments preserved
}

int main() {
    // Normalized function calls with literal normalization
    int result = complex_function(15, 20, 21);  // Literals normalized
    
    // Normalized variable declarations and canonicalized expressions
    int a;
    int b;
    int c;
    b = 5;
    a = c = 10;
    result = result + 2 * (a + b);  // Canonicalized and simplified
    
    // Control flow with dead code removed
    for (int i = 0; i < 3; i++) {
        if (i == 1) {
            continue;
            // Dead code removed
        }
        
        switch (i) {
            case 0:
                a = a + 1;         // Expanded compound assignment
                break;
            case 2: {
                // Empty case normalized
            }
            break;
            default:
                // Empty default normalized
                break;
        }
    }
    
    redeclaration_complexity();
    
    printf("Final result: %d\n", result);
    return 0;
    
    // Dead code removed
}
