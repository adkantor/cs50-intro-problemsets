#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;    // candidate's name
    int votes;      // number of votes the candidate has
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
int get_highest_vote(void);

int main(int argc, string argv[])
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

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

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
// @param name      name of the candidate who was voted for
// @return          true if valid vote else false
bool vote(string name)
{
    // Check if name is in candidate array.
    // The array is not sorted --> linear search
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // candidate found
            candidates[i].votes++;
            return true;
        }
    }

    // candidate not found
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Get highest vote
    int highest_vote = get_highest_vote();

    // Print all names with highest vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == highest_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}

// Gets the highes vote count from candidates.
// @return      count of highest votes a candidate received.
int get_highest_vote(void)
{
    int highest = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        highest = candidates[i].votes > highest ? candidates[i].votes : highest;
    }
    return highest;
}