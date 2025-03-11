#include <stdio.h>
#include <cs50.h>

// Prompt the user for the height of the pyramid
int main(void)
{
    int height;
    // while (height < 1 || height > 8)
    // {
        printf("Height: ");
        scanf("%d", &height);
    // }

    // Print the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }

    return 0;
}
