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
            //preferences[j][i]--;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                printf("Person %i beats person %i, %i-to-%i\n", i, j, preferences[i][j], preferences[j][i]);
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                printf("Person %i beats person %i, %i-to-%i\n", j, i, preferences[j][i], preferences[i][j]);
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int count = 0; count < pair_count; count++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            // look at elements i and i + 1 of pairs
            pair x = pairs[i];
            pair y = pairs[i + 1];
            if (preferences[y.winner][y.loser] > preferences[x.winner][x.loser])
            {
                pair temp = x;
                pairs[i] = y;
                pairs[i + 1] = x;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // loop thru each pair
    // try to add the connection
    // if no column is completely false, then you made a loop
    // so set things back and skip this pair, bc it creates a loop.
    
    //assume it's invalid until I confirm there's a legit column
    bool valid = false;
    for (int i = 0; i < pair_count; i++)
    {
        valid = false;
        locked[pairs[i].winner][pairs[i].loser] = true;
        
        
        for (int col = 0; col < candidate_count; col++)
        {
            
            bool all_false = true;
            for (int row = 0; row < candidate_count; row++)
            {
                // if any row in this col is true, all_false will become false
                all_false = (all_false && !locked[row][col]);
                
            }
            if (all_false)
            {
                valid = true;
                printf("Connecting person %i to person %i is valid\n", pairs[i].winner, pairs[i].loser);
                printf("Pair number %i\n", i + 1);
            }
        }
        
        if (!valid)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
            printf("Connecting person %i to person %i is invalid\n", pairs[i].winner, pairs[i].loser);
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int col = 0; col < candidate_count; col++)
    {
        bool all_false = true;
        for (int row = 0; row < candidate_count; row++)
        {
            // if any row in this col is true, all_false will become false
            all_false = (all_false && !locked[row][col]);
            
        }
        if (all_false)
        {
            printf("%s\n", candidates[col]);
        }
        else
        {
            //printf("%s loses\n", candidates[col]);
        }
    }
    return;
}

