// Runs a runoff election.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth rank preference for voter i (index of candidate is stored)
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
void update_votes(int voter);

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

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
// @param voter     index of voter
// @param rank      rank of candidate at the voter
// @param name      name of candidate
// @return          true if vote is valid
bool vote(int voter, int rank, string name)
{
    // Check if name is in candidate array.
    // The array is not sorted --> linear search
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // candidate found --> record preference
            preferences[voter][rank] = i;
            return true;
        }
    }

    // candidate not found
    return false;

}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // iterate voters and update candidates' votes based on voter's preferences
    for (int voter = 0; voter < voter_count; voter++)
    {
        update_votes(voter);
    }

    return;
}

// Updates a candidate's votes based on a voter's preferences.
// @param voter     index of voter
void update_votes(int voter)
{
    // iterate ranks bottom-up
    for (int rank = 0; rank < candidate_count; rank++)
    {
        // find candidate with current rank
        int c = preferences[voter][rank];
        // Check if candidate is eliminated.
        // If not eliminated then increase vote and return.
        // If eliminated then break and check for next rank.
        if (candidates[c].eliminated == false)
        {
            candidates[c].votes++;
            return;
        }
    }
}

// Print the winner of the election, if there is one (has more than half of votes).
// @return      true if there is a winner.
bool print_winner(void)
{
    // check if any of the candidates has more than half of votes
    int threshold = voter_count / 2 + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= threshold)
        {
            // winner found
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // no winner found
    return false;
}

// Return the minimum number of votes any remaining candidate has.
// @return      minimum number of votes
int find_min(void)
{
    int min = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            min = candidates[i].votes < min ? candidates[i].votes : min;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise.
// @param min   minimum number of votes any remaining candidate has
bool is_tie(int min)
{
    // If any candidates has higher votes than min, then there is no tie.
    // (in case of tie, every remaining candidates has the minimum number of votes)
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].eliminated == false) && (candidates[i].votes > min))
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidiates) in last place.
// @param min   minimum number of votes any remaining candidate has
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // candidates[i].eliminated = ((candidates[i].eliminated == false) && (candidates[i].votes == min));
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}
