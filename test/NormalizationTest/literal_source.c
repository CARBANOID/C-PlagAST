// TEST: Literal Normalization - Source
// Various literal formats that should normalize to standard decimal representation
// Expected: Should normalize to match literal_target.c exactly

#include <stdio.h>

int main() {
    // Hexadecimal literals with different cases
    int hex1 = 0xFF;           // Should become 255
    int hex2 = 0xDeadBeef;     // Should become 3735928559
    int hex3 = 0X1234;         // Should become 4660
    
    // Octal literals
    int oct1 = 0777;           // Should become 511
    int oct2 = 0123;           // Should become 83
    int oct3 = 0567;           // Should become 375
    
    // Binary literals (if supported)
    int bin1 = 0b1010;         // Should become 10
    int bin2 = 0B11111111;     // Should become 255
    
    // Floating point literals with various formats
    float f1 = 3.14F;          // Should become 3.14, suffix removed
    double d1 = 2.718281828;   // Should remain as is
    float f2 = 1.5e2f;         // Should become 150.0, suffix removed
    double d2 = 6.022E23;      // Should normalize exponent format
    
    // Integer literals with suffixes
    long l1 = 1000L;           // Should become 1000, suffix removed
    unsigned long ul1 = 500UL; // Should become 500, suffixes removed
    long long ll1 = 999LL;     // Should become 999, suffix removed
    
    // Character literals (should remain as-is)
    char c1 = 'A';
    char c2 = '\n';
    char c3 = '\\';
    
    // String literals (should remain as-is)
    char *s1 = "Hello World";
    char *s2 = "Line 1\nLine 2";
    
    // Complex expressions with mixed literals
    int result = 0xFF + 0777 + 0b1010;  // Should normalize all literals
    float calc = 3.14F * 2.0 + 1.5e2f;  // Should normalize suffixes
    
    // Array with literal indices and values
    int array[0x10];                     // Size should normalize to 16
    array[0] = 0xFF;                     // Index and value normalization
    array[1] = 0123;
    array[0xA] = 0b1111;                 // Index 10, value 15
    
    printf("Hex: %d, Oct: %d, Bin: %d\n", hex1, oct1, bin1);
    printf("Float: %f, Double: %f\n", f1, d1);
    printf("Result: %d, Calc: %f\n", result, calc);
    
    return 0;
}
