#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int start, int current);
void print_winner(void);
void merge_sort(pair array[], int pair_length);
void merge(pair left_half[], pair right_half[], pair array[], int pair_length);

// Start program
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Assign candidate's index to array of ranks[]
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Increment number of votes that prefer candidate i over j
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Record valid pairs next to each other in array
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort(pairs, pair_count);

    return;
}

// Recursive merge function in splitting array
void merge_sort(pair array[], int pair_length)
{
    // Base case
    if (pair_length <= 1)
    {
        return;
    }

    // Separate left and right half of array
    int middle = pair_length / 2;
    pair left_half[middle];
    pair right_half[pair_length - middle];

    // Populate each half of array
    int l = 0; // left
    int r = 0; // right

    for (; l < pair_length; l++)
    {
        if (l < middle)
        {
            left_half[l] = array[l];
        }
        else
        {
            right_half[r] = array[l];
            r++;
        }
    }

    // Recursion occurs to split left_half and right_half into two each
    merge_sort(left_half, middle);
    merge_sort(right_half, pair_length - middle);

    // Sort data in ascending order
    merge(left_half, right_half, array, pair_length);
}

// Merge function for sorting in ascending order
void merge(pair left_half[], pair right_half[], pair array[], int pair_length)
{
    // Sizes of each array
    int left_length = pair_length / 2;
    int right_length = pair_length - left_length;

    // Indices for array, left_half, and right_half
    int i = 0;
    int l = 0;
    int r = 0;

    // Compare strengths of victories of pairs
    while (l < left_length && r < right_length)
    {
        if (preferences[left_half[l].winner][left_half[l].loser] >
            preferences[right_half[r].winner][right_half[r].loser])
        {
            array[i] = left_half[l];
            l++;
            i++;
        }
        else
        {
            array[i] = right_half[r];
            r++;
            i++;
        }
    }

    // Assign data in case the other half has depleted
    while (l < left_length)
    {
        array[i] = left_half[l];
        l++;
        i++;
    }
    while (r < right_length)
    {
        array[i] = right_half[r];
        r++;
        i++;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Assign shorter variable to winner and loser
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Initially lock winner over loser
        locked[winner][loser] = true;

        // Check if locking creates a cycle
        if (check_cycle(winner, loser) == true)
        {
            locked[winner][loser] = false;
        }
    }

    return;
}

// Recursive function to check if locking pair creates a cycle
bool check_cycle(int start, int current)
{
    // Base case
    if (start == current)
    {
        return true;
    }

    // Recursively check if current points back to start
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[current][i])
        {
            if (check_cycle(start, i))
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    bool is_source = false;

    // For each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        is_source = true;

        // Check if anyone points to i
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }

        // If none points, they win
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }

    return;
}
