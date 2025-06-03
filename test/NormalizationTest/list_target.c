// TEST: List Node Normalization - Target
// Normalized list structures that should match list_source.c
// Expected: Identical AST after list normalization

#include <stdio.h>

// Function with normalized parameter list structure
int function_with_params(int first, int second, int third, char *string_param, double float_param) {
    return first + second + third;
}

// Same function normalized to identical parameter list structure
int same_function_different_format(int a, int b, int c, char *str, double f) {
    return a + b + c;
}

// Function with normalized array parameter structure
void array_function(int array1[], int size1, char array2[100], int size2) {
    printf("Array function called\n");
}

// Normalized to same structure as array_function
void same_array_function(int *array1, int size1, char *array2, int size2) {
    printf("Array function called\n");
}

int main() {
    // Function calls with normalized argument list structure
    int result1 = function_with_params(10, 20, 30, "test string", 3.14);
    
    // Normalized to same argument list structure
    int result2 = same_function_different_format(10, 20, 30, "test string", 3.14);
    
    // Array initialization with normalized list structure
    int array1[] = {1, 2, 3, 4, 5};
    
    // Already normalized list structure
    int array2[] = {1, 2, 3, 4, 5};
    
    // Normalized variable declaration list
    int var1 = 1, var2 = 2, var3 = 3;
    
    // Function calls with normalized argument structure
    array_function(array1, 5, "buffer", 6);
    
    same_array_function(array2, 5, "buffer", 6);
    
    // Nested function calls with normalized argument lists
    printf("Results: %d %d\n", 
           function_with_params(1, 2, 3, "nested", 1.0),
           same_function_different_format(4, 5, 6, "also nested", 2.0)
    );
    
    return 0;
}
