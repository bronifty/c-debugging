#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

// ========================
// Node Definition
// ========================

typedef struct node {
    int number;
    struct node *left;
    struct node *right;
} node;

// ========================
// Insert Function
// ========================

/**
 * Inserts a number into the BST.
 * If the number already exists, it is discarded.
 *
 * @param tree The root of the BST.
 * @param number The number to insert.
 * @return The root of the BST after insertion.
 */

// If the current tree node is NULL, 
// a new node is created and returned.
// If the number is less than the current node's number, 
// recurse into the left subtree.
// If the number is greater, 
// recurse into the right subtree.
// If the number is equal to an existing node's number, 
// it's considered a duplicate and is not inserted.

node* insert_bst(node *tree, int number) {
    if (tree == NULL) {
        node *new_node = (node *)malloc(sizeof(node));
        if (new_node == NULL) {
            perror("Failed to allocate memory for new BST node");
            exit(EXIT_FAILURE);
        }
        new_node->number = number;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    if (number < tree->number) {
        tree->left = insert_bst(tree->left, number);
    } else if (number > tree->number) {
        tree->right = insert_bst(tree->right, number);
    }
    return tree;
}

// ========================
// Search Function
// ========================

/**
 * Searches for a number in the BST.
 *
 * @param tree The root of the BST.
 * @param number The number to search for.
 * @return true if found, false otherwise.
 */
bool search_bst(const node *tree, int number){
    if (tree == NULL) return false;
    if (tree->number == number) return true;
    if (number < tree->number) return search_bst(tree->left, number);
    else return search_bst(tree->right, number);
}

// ========================
// In-order Traversal
// ========================

/**
 * Performs in-order traversal of the BST and prints the numbers.
 *
 * @param root The root of the BST.
 */

 // Traverses the BST in in-order 
 // (left, root, right) to print 
 // the numbers in ascending order.
 //   In-order traversal of the BST:
 //   1 2 3 4 5 
void inorder_traversal(const node *root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", root->number);
    inorder_traversal(root->right);
}

// ========================
// Free BST Memory
// ========================

/**
 * Frees all nodes in the BST.
 *
 * @param root The root of the BST.
 */
void free_bst(node *root) {
    if (root == NULL) return;
    free_bst(root->left);
    free_bst(root->right);
    free(root);
}

// ========================
// Main Function
// ========================

int main(int argc, char *argv[]) {
    if (argc < 2) {
        int predefined_numbers[] = {54, 1, 22, 9, 7, 6, 88, 44, 22, 30, 1, 3, 5, 7, 9, 6, 2, 4};
        int num_elements = sizeof(predefined_numbers) / sizeof(predefined_numbers[0]);

        argc = num_elements + 1;  // +1 for the program name
        char **new_argv = (char **) malloc(argc * sizeof(char*));
        if (new_argv == NULL) {
            perror("Failed to allocate memory for new argv");
            return EXIT_FAILURE;
        }

        new_argv[0] = argv[0];  // Program name
        for (int i = 0; i < num_elements; i++) {
            char *num_str = (char *) malloc(12 * sizeof(char));  // Enough for any 32-bit integer
            if (num_str == NULL) {
                perror("Failed to allocate memory for number string");
                return EXIT_FAILURE;
            }
            snprintf(num_str, 12, "%d", predefined_numbers[i]);
            new_argv[i + 1] = num_str;
        }

        argv = new_argv;
    }

    node *bst_root = NULL; // Root of the BST

    for (int i = 1; i < argc; i++) {
        char *endptr;
        errno = 0; // To distinguish success/failure after the call
        long val = strtol(argv[i], &endptr, 10);

        // Check for conversion errors
        if (errno != 0 || *endptr != '\0') {
            fprintf(stderr, "Invalid number '%s'. Skipping.\n", argv[i]);
            continue;
        }

        // Check for integer overflow
        if (val < INT_MIN || val > INT_MAX) {
            fprintf(stderr, "Number '%s' out of range. Skipping.\n", argv[i]);
            continue;
        }

        int number = (int)val;
        bst_root = insert_bst(bst_root, number);
    }

    // Print the BST in-order
    printf("In-order traversal of the BST:\n");
    inorder_traversal(bst_root);
    printf("\n");

    // Define the constant integer value to search for
    const int SEARCH_VALUE = 4;

    // Perform the search
    bool found = search_bst(bst_root, SEARCH_VALUE);
    printf("Number %d is %s in the tree.\n", SEARCH_VALUE, found ? "found" : "not found");

    // Free allocated memory
    free_bst(bst_root);

    return EXIT_SUCCESS;
}

/**
 *  /usr/bin/clang++ -std=c++17 -g ./balanced-tree.c -o ./balanced-tree
 *  ./balanced-tree 54 1 22 97 6 88 44 22 30 1 3 5 7 9 6 2
 *  In-order traversal of the BST:
 *  1 1 2 3 5 6 6 7 9 22 30 44 54 88 97 
 *  Number 4 is not found in the tree.
 *  ./balanced-tree 54 1 22 9 7 6 88 44 22 30 1 3 5 7 9 6 2 4
 *  In-order traversal of the BST:
 *  1 2 3 4 5 6 7 9 22 30 44 54 88 
 *  Number 4 is found in the tree.
 **/

