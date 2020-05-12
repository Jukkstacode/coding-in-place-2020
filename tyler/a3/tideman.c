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
bool wontCreatecycle(int possibleHead, int currTail);

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
        // printf("argv: %s\n",argv[i + 1]);
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");
    // printf("num voters: %d\n",voter_count);

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference index #
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            // printf("input %s\n", name);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        // for (int k = 0; k < candidate_count; k++)
        // {
        //     printf("%d, %d\n",k,ranks[k]);
        // }
        record_preferences(ranks);
        //test
        // for (int row = 0; row < candidate_count; row++)
        // {
        //     for (int col = 0; col < candidate_count; col++)
        //     {
        //         printf("%d", preferences[row][col]);
        //         if (col != candidate_count -1){printf(", ");}
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }
    
    add_pairs();
    for(int y=0; y<pair_count; y++)
        {
            int yDiff = preferences[pairs[y].winner][pairs[y].loser] - preferences[pairs[y].loser][pairs[y].winner];
            printf("pair %d: diff: %d, %d - %d\n",y, yDiff, preferences[pairs[y].winner][pairs[y].loser], preferences[pairs[y].loser][pairs[y].winner]);
        }
    sort_pairs();
    for(int y=0; y<pair_count; y++)
        {
            int yDiff = preferences[pairs[y].winner][pairs[y].loser] - preferences[pairs[y].loser][pairs[y].winner];
            printf("sort pair %d: diff: %d, %d - %d\n",y, yDiff, preferences[pairs[y].winner][pairs[y].loser], preferences[pairs[y].loser][pairs[y].winner]);
        }
    lock_pairs();
    //test
    for (int row = 0; row < candidate_count; row++)
    {
        printf("l ");
        for (int col = 0; col < candidate_count; col++)
        {
            printf("%d", locked[row][col]);
            if (col != candidate_count -1){printf(", ");}
        }
        printf("\n");
    }
    
    printf("\n");

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i=0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i],name)==0)
        {
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    bool higherRank[candidate_count];
    for (int z = 0; z < candidate_count; z++)
    {
        higherRank[z] = false;
        //printf("b %d, %d\n",z,higherRank[z]);
    }
    for (int rankNum = 0; rankNum < candidate_count-1; rankNum++)
    {
        int candidateIdx = 0;
        while(ranks[rankNum] != candidateIdx)
        {
            candidateIdx++;
        }
        higherRank[candidateIdx]=true;
        for(int i = 0; i < candidate_count; i++)
        {
            if (!higherRank[i])
            {
                preferences[candidateIdx][i]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count=0;
    for (int row = 1; row < candidate_count; row++)
    {
        for (int col = 0; col < row; col++)
        {
            // printf("row: %d, col: %d, val: %d, mirror: %d\n", row, col, preferences[row][col], preferences[col][row]);
            if (preferences[row][col] > preferences[col][row])
            {
                pairs[pair_count].winner = row;
                pairs[pair_count].loser = col;
                pair_count++;
                // printf("count: %d, win: %d, los: %d\n", pair_count-1, pairs[pair_count-1].winner, pairs[pair_count-1].loser);
            }
            else if (preferences[row][col] < preferences[col][row])
            {
                pairs[pair_count].winner = col;
                pairs[pair_count].loser = row;
                pair_count++;
                // printf("count: %d, win: %d, los: %d\n", pair_count-1, pairs[pair_count-1].winner, pairs[pair_count-1].loser);
            }
        }
    }
    printf("\n");
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int jDiff, j1Diff;
    bool changed = true;
    for(int i=0; i<pair_count && changed; i++)
    {
        changed = false;
        for(int j=0; j<pair_count-1; j++)
        {
            jDiff = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner];
            j1Diff = preferences[pairs[j+1].winner][pairs[j+1].loser] - preferences[pairs[j+1].loser][pairs[j+1].winner];
            if(jDiff<j1Diff)
            {
                pair tmp = pairs[j+1];
                pairs[j+1] = pairs[j];
                pairs[j] = tmp;
                changed = true;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i=0; i<pair_count; i++)
    {
        if (wontCreatecycle(pairs[i].winner,pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for(int i=0; i<candidate_count; i++)
    {
        // printf("checking: %d\n", i);
        bool isHead = false;
        bool isTail = false;
        int j=0;
        while(j<candidate_count && !isTail)
        {
            // printf("against: %d, head: %i, tail: %i\n", j, locked[i][j], locked[j][i]);
            if (locked[i][j])
            {
                isHead = true;
            }
            else if (locked[j][i])
            {
                isTail = true;
            }
            j++;
        }
        // printf("head: %d, tail: %d\n",isHead, isTail);
        if (isHead && !isTail)
        {
            printf("%s\n",candidates[i]);
        }
    }
    return;
}

bool wontCreatecycle(int possibleHead, int currTail)
{
    for(int i=0; i<pair_count; i++)
    {
        if (locked[currTail][i])
        {
            if (i == possibleHead)
            {
                return false;
            }
            else if (!wontCreatecycle(possibleHead, i))
            {
                return false;
            }
        }
    }
    return true;
}