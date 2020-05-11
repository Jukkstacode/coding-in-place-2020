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
void merge_sort(int left_bound, int right_bound);
int pair_compare(int pair1, int pair2);
bool pair_check(int source, int pointed_at);

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
    //Check if the name is a valid name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            //If so, enter it into ranks
            ranks[rank] = i;

            //Debug code
            printf("\nranks %d = %d\n", rank, i);

            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Loop through ranks, add to preferences array. Top rank goes above everyone else in each preference,
    //second place goes above everyone except the top person

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    //debug printing out preferences array
    printf("\nPreferences Array:\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", preferences[i][j]);
        }
        printf("\n");
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Initialize pair_count
    pair_count = 0;

    //iterate through matrix of preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //if a candidate is preferred, then record a new pair
            if (preferences[i][j] > preferences [j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }

    //Debug printing out pair count
    printf("\nPairs before sorting\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %d Loser: %d\n", pairs[i].winner, pairs[i].loser);
    }
    printf("Pairs complete\n");

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Debug sorting
    printf("Sorting started\n");

    //Bubble sort through all pairs, if a pair is larger then move it up
    pair temp_pair;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i; j < pair_count; j++)
        {
            if (pair_compare(i, j) < 0)
            {
                temp_pair.winner = pairs[j].winner;
                temp_pair.loser = pairs[j].loser;

                pairs[j].winner = pairs[i].winner;
                pairs[j].loser = pairs[i].loser;

                pairs[i].winner = temp_pair.winner;
                pairs[i].loser = temp_pair.loser;
            }
        }
    }

    //Debug printing out sorted pairs
    printf("\nPairs after sorting\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %d Loser: %d\n", pairs[i].winner, pairs[i].loser);
    }

    return;
}

//Function to compare two pairs and see which one won by a greater margin. Inputs are the indices of the pairs
//in the "pairs" array
int pair_compare(int pair1, int pair2)
{
    int margin1 = preferences[pairs[pair1].winner][pairs[pair1].loser];
    int margin2 = preferences[pairs[pair2].winner][pairs[pair2].loser];

    //Return the difference in margin of victory
    return margin1 - margin2;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Run through the pairs, checking each one to see if it creates a cycle
    for (int i = 0; i < pair_count; i++)
    {
        if (!pair_check(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    //To debug, print out locked pairs matrix
    printf("\nLocked pairs matrix:\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", locked[i][j]);
        }
        printf("\n");
    }

    return;
}

//pair_check determines if a given candidate has any already set-in preferences that lead to another candidate
bool pair_check(int source, int pointed_at)
{
    //For any arrows pointing from this candidate, check them, and if they have the "pointed_at", return true
    if (locked[source][pointed_at] == true)
    {
        return true;
    }

    //Recursion will end when it reaches a candidate who has no arrows pointing from them
    bool end_recursion = true;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[source][i] == true)
        {
            end_recursion = false;
        }
    }
    if (end_recursion == true)
    {
        return false;
    }

    //If there are arrows pointing from the candidate but they're not the one you're looking for
    //then iterate through them, if any are true then keep that number
    bool return_value = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[source][i] == true)
        {
            if (return_value == false)
            {
                return_value = pair_check(i, pointed_at);
            }
        }
    }

    //return the
    return return_value;

}

// Print the winner of the election
void print_winner(void)
{
    // Loop through all candidates, print all without any locked pairs
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate_sum = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                candidate_sum++;
            }
        }
        if (candidate_sum == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

