#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int number;
    struct node *left;
    struct node *right;
} node;

bool search(node *tree, int number){
    if (tree == NULL) return false;
    if (tree->number == number) return true;
    if (number < tree->number) return search(tree->left, number);
    else return search(tree->right, number);
}

int main(void) {
     // Create a sample binary search tree
    node *root = (node *)malloc(sizeof(node));
    root->number = 5;
    root->left = (node *)malloc(sizeof(node));
    root->left->number = 3;
    root->left->left = (node *)malloc(sizeof(node));
    root->left->left->number = 1;
    root->left->left->left = NULL;
    root->left->left->right = NULL;
    root->left->right = (node *)malloc(sizeof(node));
    root->left->right->number = 4;
    root->left->right->left = NULL;
    root->left->right->right = NULL;
    root->right = (node *)malloc(sizeof(node));
    root->right->number = 7;
    root->right->left = (node *)malloc(sizeof(node));
    root->right->left->number = 6;
    root->right->left->left = NULL;
    root->right->left->right = NULL;
    root->right->right = (node *)malloc(sizeof(node));
    root->right->right->number = 8;
    root->right->right->left = NULL;
    root->right->right->right = NULL;

    // Test the search function
    int numbers_to_search[] = {1, 4, 6, 9};
    int num_searches = sizeof(numbers_to_search) / sizeof(numbers_to_search[0]);

    for (int i = 0; i < num_searches; i++) {
        int number = numbers_to_search[i];
        bool found = search(root, number);
        printf("Number %d is %s in the tree.\n", number, found ? "found" : "not found");
    }


    free(root->right->right);
    free(root->right->left);
    free(root->right);
    free(root->left->right);
    free(root->left->left);
    free(root->left);
    free(root);

    return 0;
}