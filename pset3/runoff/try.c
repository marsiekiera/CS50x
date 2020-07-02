#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }


    tabulate();

    print_winner();

    find_min();
    int min = find_min();
    printf("min vote %d\n", min);


    bool tie = is_tie(min);
    if (tie == true)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO start (done)
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i].name))
        {
            preferences[voter][rank] = i;
            // printf("%d\n", i); // checking line - to be deleted
            return true;
        }
    }
    // TODO end (done)
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        bool end = false;
        for (int j = 0; j < candidate_count; j++)
        {
            int z = preferences[i][j];
            if (candidates[z].eliminated == false && end == false)
            {
                candidates[z].votes = candidates[z].votes + 1;
                end = true;
                printf("candidate %s\n", candidates[z].name); // checking line to be deleted
            }
        }
    }
    // TODO end
    return;
}



// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO BEGIN
    int minority;
    if (voter_count % 2 == 0)
    {
        minority = voter_count / 2;
    }
    else
    {
        minority = round(voter_count / 2);
    }
    printf("minority %d\n", minority);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > minority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // TODO END
    return false;
}


// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO begin

    int min_vote = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        if (candidates[i].votes >= candidates[i + 1].votes)
        {
            min_vote = candidates[i + 1].votes;
            return min_vote;
        }
    }

    // TODO end
    return 0;
}


// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int tie = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min && candidates[i].eliminated == false)
        {
            tie = tie + 1;
        }
        if (tie == 0)
        {
            return true;
        }
    }
    // TODO end
    return false;
}