#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j (true represents the existence of an edge pointing from candidate i to candidate j)
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner; // index of winner candidate
    int loser;  // index of loser candidate
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
bool is_cycle(pair pair, int n);
int find_source(void);

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

// Update ranks given a new vote.
// @param rank      rank of candidate at the voter
// @param name      name of candidate
// @param ranks     array of ranks representing voter?s ith preference
// @return          true if vote is valid
bool vote(int rank, string name, int ranks[])
{

    // Check if name is in candidate array.
    // The array is not sorted --> linear search
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // candidate found --> record preference
            ranks[rank] = i;
            return true;
        }
    }

    // candidate not found
    return false;

}

// Update preferences given one voter's ranks.
// @param ranks     array of ranks representing voter?s ith preference
void record_preferences(int ranks[])
{
    // N.B. preferences[i][j] represent the number of voters who prefer candidate i over candidate j
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int winner = ranks[i];
            int loser = ranks[j];
            preferences[winner][loser]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other.
// A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
void add_pairs(void)
{
    // Add all pairs of candidates where one candidate is preferred to the pairs array.
    // Also update the global variable pair_count to be the number of pairs of candidates.
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // winner of the head-to-head matchup is 'i'
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                // winner of the head-to-head matchup is 'j'
                pair_count++;
                pairs[pair_count - 1].winner = j;
                pairs[pair_count - 1].loser = i;
            }
            else
            {
                // tie --> no pair is recorded
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // using selection sort

    int first_unsorted = 0;
    for (int i = 0; i < pair_count; i++)
    {
        int ndx_highest = i;
        // sov = strength-of-victory
        int sov_highest = preferences[pairs[i].winner][pairs[i].loser] -
                          preferences[pairs[i].loser][pairs[i].winner];
        for (int j = i + 1; j < pair_count; j++)
        {
            int sov_current = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            if (sov_current > sov_highest)
            {
                ndx_highest = j;
                sov_highest = sov_current;
            }
        }
        // swap places
        if (ndx_highest != i)
        {
            pair temp;
            temp.winner = pairs[i].winner;
            temp.loser = pairs[i].loser;

            pairs[i].winner = pairs[ndx_highest].winner;
            pairs[i].loser = pairs[ndx_highest].loser;

            pairs[ndx_highest].winner = temp.winner;
            pairs[ndx_highest].loser = temp.loser;
        }

    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair pair = pairs[i];

        // check for cycle (cycles are not allowed)
        if (!is_cycle(pair, i))
        {
            // lock pair
            locked[pair.winner][pair.loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int source = find_source();
    printf("%s\n", candidates[source]);

    return;
}

// Checks if new pair creates a cycle in graph.
// @param pair      pair to investigate
// @param n         pair is n-th pair in sorted list
// @return          true if inserting pair would create cycle in the graph
bool is_cycle(pair pair, int n)
{
    // there is a cycle if after inserting the node all columns of locked array contained a true value
    for (int l = 0; l <= n; l++)
    {
        int count_true = 0;
        for (int w = 0; w <= n; w++)
        {
            if ((locked[w][l]) || (pair.winner == w && pair.loser == l))
            {
                count_true++;
            }
        }
        if (count_true == 0)
        {
            // source found, there is no cycle
            return false;
        }
    }
    return true;
}

// Finds the source node.
// @return      index of the candidate who is the source of the graph
int find_source(void)
{
    // if a candidate's column does not contain true, then it is the source
    for (int l = 0; l < candidate_count; l++)
    {
        int count_true = 0;
        for (int w = 0; w < candidate_count; w++)
        {
            if (locked[w][l])
            {
                count_true++;
            }
        }
        if (count_true == 0)
        {
            // source found, there is no cycle
            return l;
        }
    }
    return -1;
}