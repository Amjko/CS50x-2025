// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

#define HASH_CAP 676
node *table[HASH_CAP];

unsigned int word_count = 0;

// Custom case-insensitive string comparer
int custom_strcmp(const char *string1, const char *string2)
{
    while (*string1 && *string2)
    {
        char char1 = tolower(*string1);
        char char2 = tolower(*string2);

        if (char1 != char2)
        {
            return char1 - char2;
        }

        string1++;
        string2++;
    }

    return tolower(*string1) - tolower(*string2);
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hash_index = hash(word);

    node *ptr = table[hash_index];

    while (ptr != NULL)
    {
        if (custom_strcmp(word, ptr->word) == 0)
            return true;
            
        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash_index = 0;
    int word_length = strlen(word);

    // if (word_length == 1)
    if (word_length == 1 && (word[0] != '\0' && word[0] != '\''))
    {
        hash_index = (toupper(word[0]) - 'A') * 26;
    }
    else if (word_length > 1)
    {
        if (word[1] == '\'')
        {
            hash_index = (toupper(word[0]) - 'A') * 26;
        }
        else
        {
            hash_index = ((toupper(word[0]) - 'A') * 26) + (toupper(word[1]) - 'A');
        }
    }

    return hash_index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }

    int char_index = 0;
    char word[LENGTH - 1];
    char letter;

    while (fread(&letter, sizeof(char), 1, dictionary_file))
    {
        if (isalpha(letter) || (letter == '\'' && char_index > 0))
        {
            word[char_index] = letter;
            char_index++;
        }

        else if (letter == '\n')
        {
            word[char_index] = '\0';
            word_count++;
            char_index = 0;

            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                fclose(dictionary_file);
                unload();
                return false;
            }

            strcpy(new_node->word, word);
            new_node->next = NULL;

            unsigned int hash_index = hash(word);

            if (table[hash_index] == NULL)
            {
                table[hash_index] = new_node;
            }

            else
            {
                node *curr_ptr = table[hash_index];
                node *prev_ptr = NULL;
                unsigned int word_compare = strcmp(new_node->word, table[hash_index]->word);

                if (word_compare < 0)
                {
                    new_node->next = table[hash_index];
                    table[hash_index] = new_node;
                }
                else if (word_compare > 0)
                {
                    while (curr_ptr != NULL && strcmp(new_node->word, table[hash_index]->word) > 0)
                    {
                        prev_ptr = curr_ptr;
                        curr_ptr = curr_ptr->next;
                    }

                    prev_ptr->next = new_node;
                    new_node->next = curr_ptr;
                }
                else
                {
                    free(new_node);
                }
            }
        }
    }

    if (ferror(dictionary_file))
    {
        fclose(dictionary_file);
        return false;
    }

    fclose(dictionary_file);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (size_t i = 0; i < HASH_CAP; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next_node = ptr;
            ptr = ptr->next;
            free(next_node);
        }

        table[i] = NULL;
    }

    return true;
}
