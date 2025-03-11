#include <ctype.h>
#include <stdio.h>

#define CHAR_NUM 2

int main(void)
{
    char letter[CHAR_NUM];

    for (int i = 0; i < CHAR_NUM; i++)
    {
        fprintf(stdout, "Letter: ");
        scanf(" %c", &letter[i]);
    }

    if (CHAR_NUM == 2)
    {
        int hash_index = ((toupper(letter[0]) - 'A') * 26) + (toupper(letter[1]) - 'A');
        fprintf(stdout, "hash index: %i\n", hash_index);
    }
    else
    {
        fprintf(stderr, "set CHAR_NUM to 2\n");
        return 1;
    }

    return 0;
}