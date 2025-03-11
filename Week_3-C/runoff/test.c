#include <cs50.h>
#include <stdio.h>

void poops(char *name);

int main(void)
{
    char *name = get_string("Who poops?: ");
    poops(name);
    return 0;
}

void poops(char *name)
{
    printf("%s poops a lot...\n", name);
    return;
}
