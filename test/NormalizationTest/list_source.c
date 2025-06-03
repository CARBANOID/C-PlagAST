// TEST: List Node Normalization - Source
// Tests normalization of list structures in AST (parameter lists, argument lists, etc.)
// Expected: Should normalize to same AST as list_target.c

#include <stdio.h>

// Function with various parameter list patterns
int function_with_params(
    int first,
    int second,
    int third,
    char *string_param,
    double float_param
) {
    return first + second + third;
}

// Function with different parameter formatting
int same_function_different_format(int a, int b, int c, char *str, double f) {
    return a + b + c;
}

// Function with array parameters
void array_function(
    int array1[],
    int size1,
    char array2[100],
    int size2
) {
    printf("Array function called\n");
}

// Same function with different array parameter syntax
void same_array_function(int *array1, int size1, char *array2, int size2) {
    printf("Array function called\n");
}

int main() {
    // Function calls with various argument list patterns
    int result1 = function_with_params(
        10,
        20,
        30,
        "test string",
        3.14
    );
    
    // Same call with different formatting
    int result2 = same_function_different_format(10, 20, 30, "test string", 3.14);
    
    // Array initialization lists
    int array1[] = {
        1,
        2,
        3,
        4,
        5
    };
    
    // Same array with different formatting
    int array2[] = {1, 2, 3, 4, 5};
    
    // Structure initialization (if structs were supported)
    // Testing with array-like patterns instead
    
    // Multiple variable declarations (list-like)
    int var1 = 1, var2 = 2, var3 = 3;
    
    // Function calls with complex argument lists
    array_function(
        array1,
        5,
        "buffer",
        6
    );
    
    same_array_function(array2, 5, "buffer", 6);
    
    // Nested function calls (argument list within argument list)
    printf("Results: %d %d\n", 
           function_with_params(1, 2, 3, "nested", 1.0),
           same_function_different_format(4, 5, 6, "also nested", 2.0)
    );
    
    return 0;
}
