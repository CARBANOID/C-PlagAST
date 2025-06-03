// PLAGIARIZED: Algorithm Substitution - Using library functions
#include <stdio.h>
#include <string.h>

int stringLength(char* str) {
    // Algorithm substitution: use library function instead of manual loop
    return strlen(str);
}

void reverseString(char* str) {
    int len = stringLength(str);
    
    // Algorithm substitution: use different reversal approach
    char* start = str;
    char* end = str + len - 1;
    
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int compareStrings(char* str1, char* str2) {
    // Algorithm substitution: use library function
    return strcmp(str1, str2);
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
