// TEST: Expression Canonicalization - Target
// Canonicalized expressions that should match expr_source.c after normalization
// Expected: Identical AST after canonicalization

#include <stdio.h>

int main() {
    int a = 5, b = 10, c = 15, d = 20;
    int result1, result2, result3, result4;
    
    // Canonicalized commutative operations (consistent operand order)
    result1 = a + b;        // Canonical form
    result2 = a + b;        // Same canonical form as b + a
    
    // Canonicalized multiplication (consistent operand order)
    result3 = c * d;        // Canonical form
    result4 = c * d;        // Same canonical form as d * c
    
    // Canonicalized complex expressions
    int expr1 = (a + b) * c;
    int expr2 = (a + b) * c;  // Canonical form of c * (b + a)
    
    // Canonicalized nested operations (associativity normalization)
    int nested1 = a + (b + c);
    int nested2 = a + (b + c);  // Canonical form of (c + b) + a
    
    // Canonicalized mixed operations
    int mixed1 = a + b * c;
    int mixed2 = a + b * c;     // Canonical form of (b * c) + a
    
    // Canonicalized logical operations
    int logic1 = (a > 0) && (b > 0);
    int logic2 = (a > 0) && (b > 0);  // Canonical form
    
    // Canonicalized bitwise operations
    int bit1 = a | b;
    int bit2 = a | b;         // Canonical form of b | a
    
    printf("Results: %d %d %d %d\n", result1, result2, result3, result4);
    printf("Expressions: %d %d\n", expr1, expr2);
    printf("Nested: %d %d\n", nested1, nested2);
    printf("Mixed: %d %d\n", mixed1, mixed2);
    printf("Logic: %d %d\n", logic1, logic2);
    printf("Bitwise: %d %d\n", bit1, bit2);
    
    return 0;
}
