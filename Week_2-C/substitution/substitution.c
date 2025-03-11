/**
 * substitution.c -> Encrypt text with a key
 * Creation:         January 07, 2025
 * 
 * Purpose: Prompts the user for sequence of characters
 *          to encrypt with <key> to determine which letter
 *          to switch place with which.
 * 
 * Problem Source: https://cs50.harvard.edu/x/2025/psets/2/substitution/
 * 
 * Note:    Include in command-line argument the key 
 *          for substitution shift.
 * 
 * Usage: ./substitution key
 * 
 * Output: 
 *         ./substitution YTNSHKVEFXRBAUQZCLWDMIPGJO
 *         plaintext:  Hello!
 *         ciphertext: Ehbbq!
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//* Prototype functions
// Function for printing error
int error(int error_number);

// Start program
int main(int argc, char *argv[])
{
    //* Check if command-line argument is valid
    if (argc != 2)
    {
        error(1);
    }

    // Variable of key array and key's length
    char *key = argv[1];
    int key_length = strlen(key);

    // Check key length, must be 25
    if (key_length != 26)
    {
        error(2);
    }

    // Loop til end of characters
    for (int i = 0; i < key_length; i++)
    {
        // Check if key is all alphabetic
        if (!isalpha(argv[1][i]))
        {
            error(1);
        }

        // Variable for checking repeating characters
        int repeated = 0;

        // Check for repeating characters
        for (int j = 0; j < key_length; j++)
        {
            if (key[j] == key[i])
            {
                repeated++;
            }

            if (repeated >= 2)
            {
                error(3);
            }
        }
    }



    // Prompt user for plaintext
    char *text = get_string("plaintext: ");     // cs50.h function
    char *cipher_text = text;

    //* Shift letters according to key
    // Get length of text
    int text_length = strlen(text);

    // Loop through each letter
    for (int i = 0; i < text_length; i++)
    {
        // Check if is letter
        if (isalpha(text[i]))
        {
            // Shift letter uppercase
            if (isupper(text[i]))
            {
                cipher_text[i] = toupper(key[cipher_text[i] - 'A']);
            }

            // Shift letter lowercase
            if (islower(text[i]))
            {
                cipher_text[i] = tolower(key[cipher_text[i] - 'a']);
            }
        }
        else
        {
            continue;
        }
    }

    //* Print new ciphered text
    printf("ciphertext: %s\n", cipher_text);

    return 0;
}

// Function for printing error
int error(int error_number)
{
    if (error_number == 1)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }

    else if (error_number == 2)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }

    else if (error_number == 3)
    {
        printf("Key must not contain repeated characters.\n");
        exit(1);
    }
}
