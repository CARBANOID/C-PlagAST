// PLAGIARIZED: Expression Transformation - Mathematical equivalents
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    // Expression transformation: malloc(sizeof(struct Node)) -> malloc(16) assuming 64-bit
    struct Node* newNode = (struct Node*)malloc(16);  // Direct size instead of sizeof
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
    
    // Expression transformation: current != NULL -> !(current == NULL)
    while (!(current == NULL)) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    
    // Expression transformation: using arithmetic instead of direct values
    insertAtBeginning(&head, 5 + 5);      // 10
    insertAtBeginning(&head, 4 * 5);      // 20  
    insertAtBeginning(&head, 6 * 5);      // 30
    
    printList(head);
    
    return 0;
}
