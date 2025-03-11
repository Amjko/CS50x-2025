/**
 * speller.c -> Implements a dictionary's functionality
 * Creation:   January 15, 2025
 * 
 * Purpose: To print out statistics of how many words,
 *          misspells, etc. in the selected text file.
 * 
 * Problem Source: https://cs50.harvard.edu/x/2025/psets/5/speller/
 * 
 * Note:    Include in command-line argument the filename
 *          of dictionary and filename of text to check.
 * 
 * Usage: ./speller dictionary_file text_file
 * 
 * Output: 
 *        ./speller dictionaries/large texts/grimm.txt 
 *        
 *        [words]
 * 
 *         WORDS MISSPELLED:     718
 *         WORDS IN DICTIONARY:  143091
 *         WORDS IN TEXT:        103614
 *         TIME IN load:         0.05
 *         TIME IN check:        0.09
 *         TIME IN size:         0.00
 *         TIME IN unload:       0.01
 *         TIME IN TOTAL:        0.15
 */

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
