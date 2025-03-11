#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 3

int main(void)
{
    // Treat list as an int array with ARRAY_SIZE elements
    int *list = malloc(ARRAY_SIZE * sizeof(int));
    if (list == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for list");
        return 1;
    }

    // Populate array with values
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        list[i] = i + 1;
    }

    // Re-allocate memory for list array
    int *tmp = malloc((ARRAY_SIZE + 1 )* sizeof(int));
    if (tmp == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for list");
        free(list);
        return 2;
    }

    // Populate array with values from list
    for (int i = 0; i < ARRAY_SIZE + 1; i++)
    {
        tmp[i] = list[i];
        if (i == 3)
            tmp[i] = i + 1;
    }

    // Free original list
    free(list);

    // Rename new array as list
    list = tmp;

    // Print values of new list
    for (int i = 0; i < ARRAY_SIZE + 1; i++)
    {
        fprintf(stdout, "%i\n", list[i]);
    }

    // Free new list
    free(list);

    return 0;
}