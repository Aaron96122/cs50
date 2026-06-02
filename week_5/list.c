#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;

    // Bulid up list
    for (int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));
        // here we check the NULL value and free all the previous memory if the n is NULL
        if (n == NULL)
        {
            // here we free the previous memory
            unload(list);
            return 1;
        }
        // here we initalize the temporary node n
        n->number = get_number("Number: \n");
        n->next = NULL;

        // If the list is empty
        if (list == NULL)
        {
            list = n;
        }

        // If the number of the temporary node n is smaller than the current list's number
        // We prepend the node n to this list
        elif (n->number < list->number)
        {
            n->next = list;
            list = n;
        }

        // If the number belongs later in this list
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL);
                {
                    ptr->next = n;
                    break;
                }

                if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }
        }
    }
    // here we print numbers
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // here we free the memory of list
    unload(list);
    return 0;
}

void unload(node *list)
{
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}
