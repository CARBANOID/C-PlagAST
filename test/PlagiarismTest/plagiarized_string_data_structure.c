// PLAGIARIZED: Data Structure Change - Array to Pointer Arithmetic
#include <stdio.h>
#include <string.h>

int stringLength(char* str) {
    // Data structure change: pointer arithmetic instead of array indexing
    char* ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}

void reverseString(char* str) {
    int len = stringLength(str);
    
    // Data structure change: pointer-based access
    char* left = str;
    char* right = str + len - 1;
    
    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

int compareStrings(char* str1, char* str2) {
    // Data structure change: pointer arithmetic comparison
    char* p1 = str1;
    char* p2 = str2;
    
    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return *p1 - *p2;
}

int main() {
    char text[] = "hello";
    printf("Original: %s\n", text);
    
    printf("Length: %d\n", stringLength(text));
    
    reverseString(text);
    printf("Reversed: %s\n", text);
    
    char other[] = "olleh";
    int result = compareStrings(text, other);
    printf("Comparison result: %d\n", result);
    
    return 0;
}
