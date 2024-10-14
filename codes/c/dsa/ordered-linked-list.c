#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

// Function to print the linked list in order
void print_list(node *list) {
    node *ptr = list;
    while (ptr != NULL) {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }
}

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

        n->number = number;
        n->next = NULL;
 
        // if list is empty
        if (list == NULL){
            list = n;
        }

        // if number belongs earlier in list than current node, 
        // prepend to beginning of list and set the list to the new node
        // this sets "list" to always be the smallest value
        else if (n->number < list->number){
            n->next = list;
            list = n;
        }

        // if n->number is greater than the currently smallest value (list->number)
        else {
            // iterate over nodes in list
            for (node *ptr = list; ptr != NULL; ptr = ptr->next){
                // first check to see if we haven't found any node's value in the list
                // greater than n->number
                // if that is the case (n->number is larger than any in list)
                // append n node by setting ptr->next to n
                if (ptr->next == NULL){
                    ptr->next = n;
                    break;
                }
                // at this point, n->number is >= list->number
                // if n->number is >= list->number 
                // (and subsequently, ptr->number, as we iterate over the list) 
                // and n->number is < ptr->next->number ...
                // (if n->number is between the current ptr number and its next pointer's number)
                // insert node in ptr
                if (n->number < ptr->next->number){
                    // set n's next pointer to ptr's next node
                    // in order to put n between ptr and ptr->next
                    n->next = ptr->next;
                    // shift ptr's next to point to n
                    ptr->next = n;
                    break;
                }
            }
        }


    }
    


    // Print the sorted list
    print_list(list);

    // Optional: Free the allocated memory
    node *current = list;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

// /usr/bin/clang++ -std=c++17 -g ./ordered-linked-list.c -o ./ordered-linked-list
// ./ordered-linked-list 1 2 3 77 4 99 5
// should print 1 2 3 4 5 77 99