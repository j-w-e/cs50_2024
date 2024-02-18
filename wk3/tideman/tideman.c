#include <cs50.h>
#include <stdio.h>

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
int is_cycle(int winner, int loser, int endpoint);

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
        if (!strcmp(name, candidates[i]))
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
    for (int i = 0; i < candidate_count - 1; i++)
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
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // This function needs to loop through pairs[]. For each pair in pairs[], preferences[pairs[i].winner][pairs[i].loser]
    // is going to indicate the number of voters who voted for that.
    // I need to reorder pairs[i] to show that voter preference
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                pair tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;
            }
        }
    }
    return;
}

// This checks if adding the next lock to the pairings would create a cycle
// adding BC here would create a cycle:
// |   | A | B | C |
// | A | - | 1 |   |
// | B |   | - |   |
// | C | 1 |   | - |

// And here, DA would create a cycle
// |   | A | B | C | D |
// | A | - | 1 |   |   |
// | B |   | - |   | 1 |
// | C | 1 |   | - |   |
// | D |   |   |   |   |
// Look at lock[i][j]. If true:
//      look at lock[j][k], for all relevant values of k
//      if true, recurse.
//      if false, return false
int is_cycle(int winner, int loser, int endpoint)
{
    if (loser == endpoint)
    {
        return true;
    }

    if (locked[winner, loser] == false)
    {
        return false;
    }

    for (int i = 0; i < candidate_count, i != loser; i++)
    {
        if (!locked[loser, i])
            continue;
        if (!is_cycle(loser, i, endpoint))
            return false;
    }
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // here I need to check if this creates a cycle
        if (!is_cycle(pairs[i].winner, pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int edges[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        edges[i] = 0;
        for (int j = 0; j != i; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                edges++;
            }
        }
    }
    int winner = 0;
    for (i = 1; i < candidate_count; i++) 
    {
        if (edges[i] > edges[i-1]) 
        {
            winner = i;
        }
    }
    printf("The winner is %s\n", candidates[winner]);
    return;
}
