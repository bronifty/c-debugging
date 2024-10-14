// project/bst.h
#ifndef BST_H
#define BST_H

#include <iostream>

class BST {
private:
    struct Node {
        int number;
        Node* left;
        Node* right;
        Node(int val) : number(val), left(nullptr), right(nullptr) {}
    };
    Node* root;

    // Helper functions
    Node* insert(Node* node, int number);
    bool search(Node* node, int number) const;
    void inorderTraversal(Node* node) const;
    void freeMemory(Node* node);

public:
    BST();                     // Constructor
    ~BST();                    // Destructor
    void insertNumber(int number);
    bool searchNumber(int number) const;
    void printInOrder() const;
};

#endif // BST_H