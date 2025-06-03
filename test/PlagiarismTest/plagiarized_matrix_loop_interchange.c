// PLAGIARIZED: Loop Interchange and Optimization
#include <stdio.h>

void multiplyMatrices(int first[][3], int second[][3], int result[][3], int rows, int cols) {
    // Initialize result matrix first
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
        }
    }
    
    // Loop interchange: change order of k and j loops for better cache performance
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            for (int j = 0; j < cols; j++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }
}

void printMatrix(int matrix[][3], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int matrix2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int result[3][3];
    
    multiplyMatrices(matrix1, matrix2, result, 3, 3);
    
    printf("Result matrix:\n");
    printMatrix(result, 3, 3);
    
    return 0;
}
