#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);
        node *n = (node *)malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        // n->number means 'dereference the pointer, n, and access its property, number'
        // another way of saying it is go to the property of the pointer's memory address
        // another way of thinking about it is accessing the property of a referenced object in javascript, but it's a little different because of the pointer abstraction and separate memory address
        // n->number = number; will assign the value input on the command line to the property of the pointer's memory address
        n->number = number;
        // n->next = list; will assign the node data structure's next pointer (there is only next because it is a singly linked list) to the current list, which can be thought of as HEAD like in git, or the current commit, before this update is made
        // a singly-linked list adds each node by preprending it (to the left); that means the "list" (or HEAD) is always going to be penultimate or second to the most current node if we consider the one being currently added and linking back
        // the node we add links back to list (HEAD), this way it keeps track of its direct ancestor; then we change what list points to, which will be the temporary value in the loop, n, so now HEAD (list) points to the most recently added node which linked to the previously most recently added node
        // now n is free to be reallocated for the next node to be added
        n->next = list;
        // n->next = list; list = n; that is a pattern that you need to memorize for it to make sense, just like your times tables
        list = n;
    }
    // print the list
    // node *ptr = list; this creates a pointer variable with its own memory address, to point to the list, which will initially be pointing at the first memory address in the contiguous block of memory that is the list
    // while (ptr != NULL) ... ptr = ptr->next; this loops over the list, and after printing the int value at ptr->number, it reassigns ptr to the next node in the linked list (which is referenced by the pointer in the node data structure defined as *next and which is accessed with ptr->next)
    // notably, when ptr->next is referenced, it initially refers to the first item in the list (like the first index in an array); when ptr is reassigned, it moves to the next node (to the right) in the linked list 
    node *ptr = list;
    while (ptr != NULL)
    {
        printf("in the while loop\n");
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    } 
}