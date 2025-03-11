#include <stdio.h>
#include <stdlib.h>

//* Linked lists
/**
 * Link pointers that are not contiguous in memory
 */

/**
 * Node Struct
 * ----------
 * A node is generally a container of multiple values
 * 
 * typedef struct node: Initiates the struct node to be able to
 *                      be used as a data type inside the struct
 * struct node *next: Creates a pointer that points to another number
 */
typedef struct node
{
    int number;
    struct node *next;
} node;

// Pre-pending
// int main(void)
// {
//     node *list = NULL;

//     for (int i = 0; i < 3; i++)
//     {
//         node *n = malloc(sizeof(node));
//         if (n == NULL)
//         {
//             fprintf(stderr, "Failed to allocate memory with size of node");
//             return 1;
//         }
//         n->number = i + 1;
//         n->next = list;

//         list = n;
//     }

//     node *ptr = list;
//     while(ptr != NULL)
//     {
//         fprintf(stdout, "%i\n", ptr->number);
//         ptr = ptr->next;
//     }

//     return 0;
// }

// Appending
int main(void)
{
    node *list = NULL;

    for (int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fprintf(stderr, "Failed to allocate memory with size of node");
            return 1;
        }
        n->number = i + 1;
        n->next = NULL; 

        if (list == NULL)
            list = n;
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        fprintf(stdout, "%i\n", ptr->number);
    }

    node *ptr = list;
    while(ptr != NULL);
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    return 0;
}