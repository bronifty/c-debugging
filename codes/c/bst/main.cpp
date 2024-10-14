// project/main.cpp
#include <iostream>
#include "bst.h"

int main() {
    // Define an array of integers to insert into the BST
    int numbers[] = {5, 3, 1, 4, 2, 7, 6, 8, 3, 5}; // Includes duplicates: 3 and 5
    int num_elements = sizeof(numbers) / sizeof(numbers[0]);

    BST bst; // Create an instance of BST

    // Insert numbers into the BST
    for (int i = 0; i < num_elements; ++i) {
        bst.insertNumber(numbers[i]);
    }

    // Print the BST in-order
    std::cout << "In-order traversal of the BST:" << std::endl;
    bst.printInOrder();

    // Define the constant integer value to search for
    const int SEARCH_VALUE = 4;

    // Perform the search
    bool found = bst.searchNumber(SEARCH_VALUE);
    std::cout << "Number " << SEARCH_VALUE << " is " << (found ? "found" : "not found") << " in the tree." << std::endl;

    // Perform additional searches for debugging
    int debug_search_values[] = {1, 4, 6, 9};
    int debug_search_count = sizeof(debug_search_values) / sizeof(debug_search_values[0]);

    std::cout << "\nAdditional Search Results:" << std::endl;
    for (int i = 0; i < debug_search_count; ++i) {
        int number = debug_search_values[i];
        bool is_found = bst.searchNumber(number);
        std::cout << "Number " << number << " is " << (is_found ? "found" : "not found") << " in the tree." << std::endl;
    }

    return 0;
}