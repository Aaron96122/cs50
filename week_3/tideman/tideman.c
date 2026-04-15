#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
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
    // // TODO
    // return false;
    int i = 0;
    while (i < candidate_count && strcmp(name, candidates[i]) != 0)
    {
        i++;
    }
    if (i != candidate_count)
    {
        ranks[rank] = i;
        return true;
    }
    else
    {
        return false;
    }
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int i;
    int j;
    int index;
    for (i = 0; i < candidate_count - 1; i++)
    {
        index = i + 1;
        for (j = index; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            // printf("Candidate %i is %s\nCandidate %i is %s\n", ranks[i], candidates[ranks[i]],
            // ranks[j], candidates[ranks[j]]); printf("Preferences are: %i\n",
            // preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int i, j;
    int diff;
    for (i = 0; i < candidate_count - 1; i++)
    {
        for (j = i + 1; j < candidate_count; j++)
        {
            diff = preferences[i][j] - preferences[j][i];
            if (diff != 0)
            {
                if (diff > 0)
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                }
                pair_count++;
            }
        }
    }
    // printf("count: %i\n", pair_count);
    // int m;
    // for (m = 0; m < pair_count; m++)
    // {
    //     printf("Winner: %s(%i); Loser: %s(%i); margin: %i-%i\n",
    //             candidates[pairs[m].winner], pairs[m].winner,
    //             candidates[pairs[m].loser], pairs[m].loser,
    //             preferences[pairs[m].winner][pairs[m].loser],
    //             preferences[pairs[m].loser][pairs[m].winner]);
    // }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int i, j;
    int strength;
    int target, index;
    pair temp;
    for (i = 0; i < pair_count - 1; i++)
    {
        index = i;
        for (j = i + 1; j < pair_count; j++)
        {
            strength = preferences[pairs[index].winner][pairs[index].loser];
            target = preferences[pairs[j].winner][pairs[j].loser];
            if (target > strength)
            {
                index = j;
            }
        }
        temp = pairs[i];
        pairs[i] = pairs[index];
        pairs[index] = temp;
    }
    // int m;
    // for (m = 0; m < pair_count; m++)
    // {
    //     printf("Winner: %s(%i); Loser: %s(%i); margin: %i-%i\n",
    //             candidates[pairs[m].winner], pairs[m].winner,
    //             candidates[pairs[m].loser], pairs[m].loser,
    //             preferences[pairs[m].winner][pairs[m].loser],
    //             preferences[pairs[m].loser][pairs[m].winner]);
    // }
    return;
}

bool check_cycles(int loser, int winner)
{
    if (loser == winner)
    {
        return true;
    }

    int i;
    for (i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (check_cycles(i, winner) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int i;
    int winner, loser;
    for (i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        if (check_cycles(loser, winner) == false)
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int i;
    int index;
    int j;
    for (i = 0; i < candidate_count; i++)
    {
        j = 0;
        while (j < candidate_count && locked[j][i] == false)
        {
            j++;
        }
        if (j == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
