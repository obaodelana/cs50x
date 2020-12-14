#include <stdio.h>
#include <string.h>
#include <cs50.h>

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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
int candidate_count = 0;

// Stop execution in recursive function
bool step_over = false;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool check_source(int index);
void lock_pairs(void);
void print_winner(void);

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

    // print_table();
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
        if (strcmp(candidates[i], name) == 0)
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
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (ranks[j] == ranks[i])
            {
                continue;
            }

            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Testing purposes
// void print_table(void)
// {
//     for (int i = 0; i < candidate_count; i++)
//     {
//         for (int j = 0; j < candidate_count; j++)
//         {
//             printf("%i ", preferences[i][j]);
//             fflush(stdout);
//         }
//
//         printf("\n");
//     }
// }

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Adjacent groups of zeros
    for (int i = 0, j = 0; i < candidate_count - 1; i++, j++)
    {
        // If ith row > ith + 1 row winner is ith row else winner is ith + 1
        if (preferences[i][j + 1] > preferences[i + 1][j])
        {
            pairs[pair_count].winner = i;
            pairs[pair_count].loser = i + 1;
            pair_count++;
        }

        else if (preferences[i][j + 1] < preferences[i + 1][j])
        {
            pairs[pair_count].winner = i + 1;
            pairs[pair_count].loser = i;
            pair_count++;
        }
    }

    // first and last group of zeros
    if (preferences[0][candidate_count - 1] > preferences[candidate_count - 1][0])
    {
        pairs[pair_count].winner = 0;
        pairs[pair_count].loser = candidate_count - 1;
        pair_count++;
    }

    else if (preferences[0][candidate_count - 1] < preferences[candidate_count - 1][0])
    {
        pairs[pair_count].winner = candidate_count - 1;
        pairs[pair_count].loser = 0;
        pair_count++;
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Use an insertion sort to sort the array in order of its strength
    for (int i = 1; i <= pair_count - 1; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (preferences[pairs[j + 1].winner][pairs[j + 1].loser] > preferences[pairs[j].winner][pairs[j].loser])
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }

    // Testing purposes
    // printf("\n");
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("Pair %i (winner: %i, loser: %i, strength: %i)\n", i + 1, pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    // }
    // printf("\n");
}

// Create a chain and if the end of the chain has the winner, it's a cycle
bool check_lock(int w, int l)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (step_over)
        {
            return false;
        }

        if (l == pairs[i].winner)
        {
            if (locked[l][pairs[i].loser])
            {
                if (pairs[i].loser == w)
                {
                    step_over = true;
                    return false;
                }

                check_lock(w, pairs[i].loser);
            }
        }
    }

    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        step_over = false;
        if (check_lock(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    int falseCounter = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                falseCounter = 0;
                break;
            }

            falseCounter++;
        }

        if (falseCounter >= candidate_count)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
}
