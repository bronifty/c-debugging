// project/bst.cpp
#include "bst.h"

// Constructor: Initializes an empty BST
BST::BST() : root(nullptr) {}

// Destructor: Frees all allocated memory
BST::~BST() {
    freeMemory(root);
}

// Private Insert Helper
BST::Node* BST::insert(Node* node, int number) {
    if (node == nullptr) {
        // Insert new node
        return new Node(number);
    }

    if (number < node->number) {
        node->left = insert(node->left, number);
    } else if (number > node->number) {
        node->right = insert(node->right, number);
    }
    // If number == node->number, it's a duplicate; do not insert
    return node;
}

// Public Insert Function
void BST::insertNumber(int number) {
    root = insert(root, number);
}

// Private Search Helper
bool BST::search(Node* node, int number) const {
    if (node == nullptr) {
        return false;
    }

    if (number == node->number) {
        return true;
    } else if (number < node->number) {
        return search(node->left, number);
    } else {
        return search(node->right, number);
    }
}

// Public Search Function
bool BST::searchNumber(int number) const {
    return search(root, number);
}

// Private In-order Traversal Helper
void BST::inorderTraversal(Node* node) const {
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left);
    std::cout << node->number << " ";
    inorderTraversal(node->right);
}

// Public In-order Traversal Function
void BST::printInOrder() const {
    inorderTraversal(root);
    std::cout << std::endl;
}

// Private Memory Cleanup Helper
void BST::freeMemory(Node* node) {
    if (node == nullptr) {
        return;
    }
    freeMemory(node->left);
    freeMemory(node->right);
    delete node;
}