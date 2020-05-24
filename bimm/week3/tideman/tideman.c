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
bool noCycle(int lose_cand, int win_cand);
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
        //print updated preferences grid after each vote
//        for (int m = 0; m < candidate_count; m++)
//        {
//            for (int n = 0; n < candidate_count; n++)
//            {
//                printf("%i ", preferences[m][n]);
//            }
//            printf("\n");
//        }

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
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength[pair_count];
    for (int n = 0; n < pair_count; n++)
    {
        strength[n] = preferences[pairs[n].winner][pairs[n].loser];
//      printf("Unsorted pairs: %i,%i = %i",pairs[n].winner,pairs[n].loser,strength[n]);
//      printf("\n");
    }
    for (int n = 0; n < pair_count; n++)
    {
        for (int m = n+1; m < pair_count; m++)
        {
            if (strength[m] > strength[n])    
            {
                int temp;
                pair p_temp;
                temp = strength[n];
                p_temp = pairs[n];
                strength[n] = strength[m];
                pairs[n] = pairs[m];
                strength[m] = temp;
                pairs[m] = p_temp;
            }
        }
    }
//    for (int n = 0; n < 6; n++)
//    {
//        printf("Sorted pairs: %i,%i = %i",pairs[n].winner,pairs[n].loser,strength[n]);
//        printf("\n");
//    }
    return;

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        //check for a path from the loser to the winner
        if(!noCycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
//    for (int m = 0; m < candidate_count; m++)
//        {
//            for (int n = 0; n < candidate_count; n++)
//            {
//                printf("%i ", locked[m][n]);
//            }
//            printf("\n");
//        }
        printf("\n");
    return;
}
//only lock in if it doesn't create a cycle
bool noCycle (int start, int end)
{
    if (start == end)
    {
        return true; //that's a cycle
    }
    else
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[start][i]) //found another path
        {
            return noCycle (i, end);
        }
    }
    return false; //no cycle
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int arrows_away = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                arrows_away++;
            }
        }
        if (arrows_away == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

