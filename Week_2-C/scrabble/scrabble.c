/**
 * scrabble.c -> Game of scrabble
 * Creation:    January 07, 2025
 * 
 * Purpose: Query # number of users for words
 *          wherein the user with most points
 *          (calculated via letters corresponding
 *          random amount of points) wins.
 * 
 * Problem Source: https://cs50.harvard.edu/x/2025/psets/2/scrabble/
 * 
 * Usage: ./scrabble
 * 
 * Output: 
 *         Player 1: red
 *         Player 2: wheelbarrow
 *         Player 2 wins!
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototype function
int get_score(int length, char *word);

// Array for each letter in the alphabet
// const char letter[26] =
// {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

// Array for points of each letter
const int points[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Amount of players
const int N = 2;

int main(void)
{
    //* Prompt players for a word.
    char *player[N];

    // Loop to prompt each player
    for (int i = 0; i < N; i++)
    {
        player[i] = get_string("Player %i: ", i + 1);   // cs50.h function
    }

    //* Determine each player's score
    int length[N];
    int score[N];

    // Loop to get word length of each player's word
    for (int i = 0; i < N; i++)
    {
        length[i] = strlen(player[i]);
        score[i] = get_score(length[i], player[i]);
    }

    //* Determine highest score and winner
    int winner = 0;
    int winning_score = 0;
    bool tie = false;

    // Keep track of who has more points
    for (int i = 0; i < N; i++)
    {
        if (score[i] > winning_score)
        {
            winner = i;
            winning_score = score[i];
            tie = false;
        }

        else if (score[i] == winning_score)
        {
            tie = true;
        }
    }

    // Print who wins if not tie
    if (!tie)
    {
        printf("Player %i wins!\n", winner + 1);
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

//* Function to calculate score of a player's word
int get_score(int length, char *word)
{
    int score = 0;
    int letter = 0;

    //* Loop to validate only letters
    for (int i = 0; i < length; i++)
    {
        // Check if symbol is a letter and ensure capitalized
        if (isalpha(word[i]))
        {
            // 'A' - 'A' = 0 | 'Z' - 'A' = 26
            letter = toupper(word[i]);
            letter -= 'A';
            score += points[letter];
        }
        else
        {
            score += 0;
        }
    }

    return score;
}
