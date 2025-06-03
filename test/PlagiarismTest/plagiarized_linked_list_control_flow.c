// PLAGIARIZED: Control Flow Restructuring - Using different loop structures
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    newNode->next = *head;
    *head = newNode;
}

void printList(struct Node* head) {
    struct Node* current = head;
    printf("List: ");
    
    // Using do-while instead of while loop
    if (current != NULL) {
        do {
            printf("%d ", current->data);
            current = current->next;
        } while (current != NULL);
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    
    // Using a for loop instead of individual calls
    int values[] = {30, 20, 10};
    for (int i = 0; i < 3; i++) {
        insertAtBeginning(&head, values[i]);
    }
    
    printList(head);
    
    return 0;
}
