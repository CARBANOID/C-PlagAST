// ORIGINAL: Simple Array Sum with Multiple Functions
#include <stdio.h>

int calculateSum(int array[], int length) {
    int total = 0;
    for (int i = 0; i < length; i++) {
        total += array[i];
    }
    return total;
}

double calculateAverage(int array[], int length) {
    int sum = calculateSum(array, length);
    return (double)sum / length;
}

void printArray(int array[], int length) {
    printf("Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    printArray(numbers, size);
    
    int sum = calculateSum(numbers, size);
    double avg = calculateAverage(numbers, size);
    
    printf("Sum: %d\n", sum);
    printf("Average: %.2f\n", avg);
    
    return 0;
}
