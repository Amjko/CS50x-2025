/**
 * readability.c -> Determine reading comprehension
 * Creation:        January 07, 2025
 * 
 * Purpose: Query user of sentences or paragraphs to
 *          determine the approximate grade level of
 *          the reading comprehension of the text.
 * 
 * Usage: ./readability
 * 
 * Output: 
 *         Text: One fish. Two fish. Red fish. Blue fish.
 *         Before Grade 1
 */

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//* Prototype functions
// Determine average number of letters per 100 words
float get_avg_letter(int length, char *text);

// Determine average number of sentences per 100 words
float get_avg_sentence(int length, char *text);

// Coleman-Liau index outputs approximate grade level
int coleman_liau_index(float avg_letters, float avg_sentences);

// Start program
int main(void)
{
    // Prompt user for text
    char *text = get_string("Text: ");      // cs50.h function

    // Get text's length
    int text_length = strlen(text);

    //* Output approximate grade level
    float avg_letters = get_avg_letter(text_length, text);
    float avg_sentences = get_avg_sentence(text_length, text);
    coleman_liau_index(avg_letters, avg_sentences);

    return 0;
}

// Determine average number of letters per 100 words
float get_avg_letter(int length, char *text)
{
    float avg_letters = 0;
    float total_letters = 0;
    float total_words = 0;

    //* Count letters and words
    for (int i = 0; i < length; i++)
    {
        // Count total letters
        if (isalpha(text[i]))
        {
            total_letters++;
        }

        // Count total words
        else if (isspace(text[i]))
        {
            total_words++;
        }
    }

    // Calculate average
    total_words++;
    avg_letters = (total_letters / total_words) * 100;

    // printf("letters: %f\n", total_letters);
    // printf("words: %f\n", total_words);
    // printf("average: %f\n", avg_letters);

    return avg_letters;
}

// Determine average number of sentences per 100 words
float get_avg_sentence(int length, char *text)
{
    float avg_sentences = 0;
    float total_sentences = 0;
    float total_words = 0;

    //* Count letters and words
    for (int i = 0; i < length; i++)
    {
        // Count total sentences
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            total_sentences++;
        }

        // Count total words
        if (isspace(text[i]))
        {
            total_words++;
        }
    }

    // Calculate average
    total_words++;
    avg_sentences = (total_sentences / total_words) * 100;

    // printf("sentences: %f\n", total_sentences);
    // printf("words: %f\n", total_words);
    // printf("average: %f\n", avg_sentences);

    return avg_sentences;
}

// Coleman-Liau index outputs approximate grade level
int coleman_liau_index(float avg_letters, float avg_sentences)
{
    // Calculate index
    float index = (0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8;

    // printf("index: %f\n", index);

    // Print approx grade level
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        index = roundf(index);
        printf("Grade %i\n", (int)index);
    }

    exit(0);
}
