/**
 * plurality.c -> Determine winner of candidacy
 * Creation:      January 09, 2025
 * 
 * Purpose: Prompts the user for names of running candidates
 *          then calculate the winner of who has the most
 *          votes.
 * 
 * Problem Source: https://cs50.harvard.edu/x/2025/psets/3/plurality/
 * 
 * Note:    Include in command-line argument the names of
 *          the candidates.
 * 
 * Usage: ./plurality name1 name2 name3
 * 
 * Output: 
 *         ./plurality Alice Bob Charlie 
 *         Number of voters: 3
 *         Vote: Alice
 *         Vote: Alice
 *         Vote: Bob
 *         Alice
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");        // cs50.h function

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char *name = get_string("Vote: ");                  // cs50.h function

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name)
{
    // TODO
    // Check if name matches any of candidates' name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // Check for highest votes
    int highest_vote = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_vote)
        {
            highest_vote = candidates[i].votes;
        }
    }

    // Print candidates with highest votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (highest_vote == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
