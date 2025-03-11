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

// Prime number to prevent chances of collisions
#define TABLE_SIZE 200003
node *table[TABLE_SIZE];

unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Find the index the word lies in
    unsigned int hash_value = hash(word);
    unsigned int hash_index = hash_value % TABLE_SIZE;

    node *ptr = table[hash_index];

    // Check if the word has correct spelling
    while (ptr != NULL)
    {
        const char *table_word = ptr->word;
        const char *curr_word = word;

        while (*table_word && *curr_word)
        {
            char char1 = *curr_word;
            char char2 = *table_word;

            if (tolower(char1) != tolower(char2))
                break;

            table_word++;
            curr_word++;
        }

        if (*table_word == '\0' && *curr_word == '\0')
            return true;
            
        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Decrease hash collisions by getting randomized values
    unsigned int hash_value = 1031;
    while (*word)
    {
        hash_value = (hash_value * 33) + tolower(*word);
        word++;
    }

    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }

    // Hash word on it's corresponding hash_index
    char word[LENGTH - 1];
    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        word_count++;

        // Node for hashing the word into hash table
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(dictionary_file);
            unload();
            return false;
        }
        strcpy(new_node->word, word);

        // Find the index the word lies in
        unsigned int hash_value = hash(word);
        unsigned int hash_index = hash_value % TABLE_SIZE;

        // Prepend in case of collision
        new_node->next = table[hash_index];
        table[hash_index] = new_node;
    }

    // Avoid accessing error'ed file
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
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (size_t i = 0; i < TABLE_SIZE; i++)
    {
        node *ptr = table[i];

        // Free only existing nodes
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
