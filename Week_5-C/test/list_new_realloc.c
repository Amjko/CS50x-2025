#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 3

int main(void)
{
    // Initial allocation
    int *list = malloc(ARRAY_SIZE * sizeof(int));
    if (list == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for list array\n");
        return 1;
    }

    // Populate array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        list[i] = i + 1;
    }

    /**
     *  Re-allocate memory for list array
     * 
     * @ptr:  Argument where to copy values from
     * @size: Size of array
     * 
     * Usage: type *ptr = realloc(list, ARRAY_SIZE);
     * 
     * Note: When realloc is successful, it automatically
     *       frees the allocated memory of the initial array
     */
    int *tmp = realloc(list, (ARRAY_SIZE + 1) * sizeof(int));
    if (tmp == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory for list array\n");
        free(list);
        return 2;
    }

    list = tmp;
    list[3] = 4;

    // Print out values
    for (int i = 0; i < ARRAY_SIZE + 1; i++)
    {
        fprintf(stdout, "%i\n", list[i]);
    }

    free(list);

    return 0;
}