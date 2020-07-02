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
}
pair;

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

// TODO ------------------------------------------------------------------------------

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    //TODO end
    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1;
            // printf("%d\n", preferences[ranks[i]][ranks[j]]);
        }
    }
    //TODO END
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                // printf("Pair[%d]winner = %d\n", pair_count, pairs[pair_count].winner);
                pairs[pair_count].loser = j;
                // printf("Pair[%d]loser = %d\n", pair_count, pairs[pair_count].loser);
                pair_count = pair_count + 1;
            }
        }
    }
    // TODO END
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int sort_count = 0;
    int temp_winner;
    int temp_loser;

    do
    {
        sort_count = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                temp_winner = pairs[i].winner;
                temp_loser = pairs[i].loser;

                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;

                pairs[i + 1].winner = temp_winner;
                pairs[i + 1].loser = temp_loser;

                sort_count = sort_count + 1;
            }
        }
    }
    while (sort_count > 0);
    // TODO END
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        for (int j = i; j > 0; j--)
        {
            if (pairs[j].winner == pairs[j - 1].loser && pairs[0].winner == pairs[i].loser)
            {
                locked[pairs[i].winner][pairs[i].loser] = false;
            }
        }
    }
    // TODO END
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int matrix2[candidate_count];
    // check if candidate is loser in any pair
    for (int m = 0; m < candidate_count; m++)
    {
        matrix2[m] = 0;
        for (int n = 0; n < candidate_count; n++)
        {
            if (locked[n][m] == true)
            {
                matrix2[m] = 1;
            }
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (matrix2[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    // TODO END
}