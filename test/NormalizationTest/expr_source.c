// TEST: Expression Canonicalization - Source
// Tests canonicalization of commutative operations and expression ordering
// Expected: Should normalize to same AST as expr_target.c

#include <stdio.h>

int main() {
    int a = 5, b = 10, c = 15, d = 20;
    int result1, result2, result3, result4;
    
    // Commutative operations in different orders
    result1 = a + b;        // Should canonicalize operand order
    result2 = b + a;        // Should be same as above after canonicalization
    
    // Multiplication with different operand orders
    result3 = c * d;        // Should canonicalize operand order
    result4 = d * c;        // Should be same as above after canonicalization
    
    // Complex expressions with parentheses
    int expr1 = (a + b) * c;
    int expr2 = c * (b + a);  // Should normalize to same as expr1
    
    // Nested commutative operations
    int nested1 = a + (b + c);
    int nested2 = (c + b) + a;  // Should normalize to same as nested1
    
    // Mixed operations with different precedence
    int mixed1 = a + b * c;
    int mixed2 = (b * c) + a;   // Should normalize to same as mixed1
    
    // Logical operations
    int logic1 = (a > 0) && (b > 0);
    int logic2 = (b > 0) && (a > 0);  // Should normalize to same as logic1
    
    // Bitwise operations
    int bit1 = a | b;
    int bit2 = b | a;         // Should normalize to same as bit1
    
    printf("Results: %d %d %d %d\n", result1, result2, result3, result4);
    printf("Expressions: %d %d\n", expr1, expr2);
    printf("Nested: %d %d\n", nested1, nested2);
    printf("Mixed: %d %d\n", mixed1, mixed2);
    printf("Logic: %d %d\n", logic1, logic2);
    printf("Bitwise: %d %d\n", bit1, bit2);
    
    return 0;
}
