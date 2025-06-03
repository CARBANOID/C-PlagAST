// ORIGINAL: String Processing Functions
#include <stdio.h>
#include <string.h>

int stringLength(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void reverseString(char* str) {
    int len = stringLength(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int compareStrings(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
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
