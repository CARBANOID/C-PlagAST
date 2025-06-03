// PLAGIARIZED: Loop Unrolling and Statement Reordering
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createTreeNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->value = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* insert(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createTreeNode(data);
    }
    
    if (data < root->value) {
        root->left = insert(root->left, data);
    } else if (data > root->value) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->value);
        inorderTraversal(root->right);
    }
}

int main() {
    struct TreeNode* root = NULL;
    
    // Loop unrolling - instead of using a loop, manually unroll insertions
    // Statement reordering - change the order of operations
    printf("Inorder traversal: ");
    
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    
    inorderTraversal(root);
    printf("\n");
    
    return 0;
}
