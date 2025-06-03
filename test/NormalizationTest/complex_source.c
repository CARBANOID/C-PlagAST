// TEST: Complex Normalization Scenarios - Source
// Non-normalized version with various constructs that should normalize to complex_target.c
// Expected: Should normalize to match complex_target.c exactly

#include <stdio.h>

// Complex function with various normalizable constructs
int complex_function(int a, int b, int c) {
    // // Multi-variable declarations that should be split
    int x, y = a + b, z;
    int result1, result2 = 0, result3;
    
    // // Complex expressions that should be canonicalized
    result1 = c * (b + a) + (a + b) * c;  // Should canonicalize to consistent order
    result2 += y * 2;                     // Compound assignment should expand
    result3 = z = x = 42;                 // Chained assignment
    
    // // Control flow with dead code
    if (a > 0) { 
        return result1 + result2;
        printf("This is dead code after return\n");  // Should be removed
        int dead_var = 999;                           // Should be removed
    } else if (b > 0) {
        x += 10;                          // Compound assignment should expand
        return x * result2;
        x += 20 ;                            // Dead code - invalid break
    }
    
    // Empty blocks and type casts
    if (c == 0) {
        {}  // Empty block should normalize
    } else {
        printf("Non-empty else\n");
    }
    
    // Various literal formats that should normalize
    int hex_value = 0xFF;              // Should normalize to decimal 255
    int octal_value = 0777;            // Should normalize to decimal 511
    double scientific = 1.5e2F;       // Should normalize to 150.0, suffix removed
    
    // // Complex nested expressions with type casts
    return (a * b + a * b) + (hex_value + octal_value) - (int)scientific;
}

// Function with consecutive redeclarations
void redeclaration_complexity() {
    int var;
    int var;                        // Consecutive redeclaration should normalize
    var = 10;
    
    {
        int var = 20;              // Valid scope redeclaration
        {
            int var;               // Another scope
            int var;               // Consecutive redeclaration should normalize
            var = 30;
        }
    }
    
    // Array and pointer declarations with casts
    int array[5], *ptr, value;
    array[0] = array[1] = array[2] = (int)100L;  // Type cast and suffix removal
}

int main() {
    // Function calls with various literal formats
    int result = complex_function(0xF, 020, 0b10101);  // Mixed number formats
    
    // Multi-variable declarations and complex expressions
    int a, b = 5, c;
    a = c = 10;
    result += 2 * (a + b);         // Compound assignment with canonicalization
    
    // Control flow with dead code
    for (int i = 0; i < 3; i++) {
        if (i == 1) {
            continue;
            printf("Dead after continue\n");  // Should be removed
        }
        
        switch (i) {
            case 0:
                a += 1;            // Compound assignment
                break;
            case 2: {
                {}                 // Empty case block
            }
            break;
            default:
                ;                  // Empty default
                break;
        }
    }
    
    redeclaration_complexity();
    
    printf("Final result: %d\n", result);
    return 0;
    
    // Dead code after return
    printf("This should be removed\n");
    int unreachable = 42;
}
