// PLAGIARIZED: Variable Reordering and Renaming
#include <stdio.h>

int computeTotal(int data_array[], int array_size) {
    int running_sum = 0;
    for (int counter = 0; counter < array_size; counter++) {
        running_sum += data_array[counter];
    }
    return running_sum;
}

double computeMean(int data_array[], int array_size) {
    int total_sum = computeTotal(data_array, array_size);
    return (double)total_sum / array_size;
}

void displayArray(int data_array[], int array_size) {
    printf("Array: ");
    for (int counter = 0; counter < array_size; counter++) {
        printf("%d ", data_array[counter]);
    }
    printf("\n");
}

int main() {
    int data_values[] = {10, 20, 30, 40, 50};
    int array_length = 5;
    
    displayArray(data_values, array_length);
    
    int total_sum = computeTotal(data_values, array_length);
    double mean_value = computeMean(data_values, array_length);
    
    printf("Sum: %d\n", total_sum);
    printf("Average: %.2f\n", mean_value);
    
    return 0;
}
