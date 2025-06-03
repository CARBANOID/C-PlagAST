// PLAGIARIZED: Dead Code Insertion - Added unused functions and variables
#include <stdio.h>

// Dead function - never called
void unusedFunction() {
    int dummy = 42;
    printf("This is never executed\n");
}

// Dead variable in scope
static int global_unused = 999;

int calculateSum(int array[], int length) {
    // Dead variables
    int unused_var = 100;
    char dead_buffer[50];
    
    int total = 0;
    for (int i = 0; i < length; i++) {
        total += array[i];
    }
    
    // Dead code block
    if (0) {
        printf("Dead code block\n");
        unused_var = 200;
    }
    
    return total;
}

double calculateAverage(int array[], int length) {
    // Another dead variable
    float meaningless = 3.14f;
    
    int sum = calculateSum(array, length);
    return (double)sum / length;
}

void printArray(int array[], int length) {
    printf("Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // Dead assignment
    int temp = length * 2;
}

// Another unused function
int deadFunction(int x, int y) {
    return x + y + global_unused;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    // Dead variable in main
    int local_dead = 777;
    
    printArray(numbers, size);
    
    int sum = calculateSum(numbers, size);
    double avg = calculateAverage(numbers, size);
    
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", avg);
    
    return 0;
}
