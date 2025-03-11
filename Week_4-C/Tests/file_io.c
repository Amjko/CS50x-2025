#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Open file called "phonebook.csv" for writing continuously (a)
    FILE *file = fopen("phonebook.csv", "a");

    // Error in case fopen returns a NULL
    if (file == NULL)
    {
        // perror means to print error in command line
        // perror automatically appends (\n) text
        perror("Error opening file");

        fclose(file);
        return 1;
    }

    // Inquire user for a name and a number
    char *name = get_string("name: ");
    char *number = get_string("number: ");

    // Error in case fprintf cannot print into file
    if (fprintf(file, "%s, %s\n", name, number) < 0)
    {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    // Print the name and number inquired, into opened file
    fprintf(file, "%s, %s\n", name, number);

    // Close file
    fclose(file);

    return 0;
}
