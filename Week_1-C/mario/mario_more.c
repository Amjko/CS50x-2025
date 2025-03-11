/**
 * mario_more.c -> Pyramid hashtag program
 * Creation:       January 03, 2025
 * 
 * Purpose: Prompts the user for desired height of a pyramid
 *          to be printed in terminal with hashtags.
 * 
 * Usage: ./mario
 * 
 * Output: 
 *         Height: 4
 *            #  #
 *           ##  ##
 *          ###  ###
 *         ####  ####
 */

#include <stdio.h>
// #include <cs50.h>


int main(void)
{   
    // Prompt user for height
    int height;
    // Remove commented code for added height limits
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
