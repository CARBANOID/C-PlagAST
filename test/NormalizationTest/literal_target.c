// TEST: Literal Normalization - Target
// All literals normalized to standard decimal representation
// Expected: Should exactly match literal_source.c after normalization

#include <stdio.h>

int main() {
    // Hexadecimal literals normalized to decimal
    int hex1 = 255;            // 0xFF normalized
    int hex2 = 3735928559;     // 0xDeadBeef normalized
    int hex3 = 4660;           // 0X1234 normalized
    
    // Octal literals normalized to decimal
    int oct1 = 511;            // 0777 normalized
    int oct2 = 83;             // 0123 normalized
    int oct3 = 375;            // 0567 normalized
    
    // Binary literals normalized to decimal
    int bin1 = 10;             // 0b1010 normalized
    int bin2 = 255;            // 0B11111111 normalized
    
    // Floating point literals with suffixes removed
    float f1 = 3.14;           // F suffix removed
    double d1 = 2.718281828;   // Already normalized
    float f2 = 150.0;          // 1.5e2f normalized and suffix removed
    double d2 = 6.022e23;      // Exponent format normalized (E -> e)
    
    // Integer literals with suffixes removed
    long l1 = 1000;            // L suffix removed
    unsigned long ul1 = 500;   // UL suffixes removed
    long long ll1 = 999;       // LL suffix removed
    
    // Character literals (unchanged)
    char c1 = 'A';
    char c2 = '\n';
    char c3 = '\\';
    
    // String literals (unchanged)
    char *s1 = "Hello World";
    char *s2 = "Line 1\nLine 2";
    
    // Complex expressions with all literals normalized
    int result = 255 + 511 + 10;        // All literals normalized
    float calc = 3.14 * 2.0 + 150.0;    // All suffixes removed
    
    // Array with normalized literal indices and values
    int array[16];                       // 0x10 normalized to 16
    array[0] = 255;                      // 0xFF normalized
    array[1] = 83;                       // 0123 normalized
    array[10] = 15;                      // 0xA -> 10, 0b1111 -> 15
    
    printf("Hex: %d, Oct: %d, Bin: %d\n", hex1, oct1, bin1);
    printf("Float: %f, Double: %f\n", f1, d1);
    printf("Result: %d, Calc: %f\n", result, calc);
    
    return 0;
}
