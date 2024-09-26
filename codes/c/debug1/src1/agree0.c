// Comparing against lowercase char


#include <stdio.h>

int main(void)
{
    // Prompt user to agree
    char c = 'y';

    // Check whether agreed
    if (c == 'y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'n')
    {
        printf("Not agreed.\n");
    }
}
