// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (26 * 26);

// Hash table
node *table[N];

// size counter
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int this_hash = hash(word);
    node *trav = table[this_hash];
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
            // printf("Word %s is spelled right", word);
        }
        trav = trav->next;
    }
    //node
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // Use the 1st two letters, ASCII math, 
    // kind of Excel style, base 26
    int n = strlen(word);
    if (n == 1)
    {
        return (toupper(word[0]) - 65);
    }
    else if (isalpha(word[1]) != 0)
    {
        // first letter (minus 65)
        // plus 26 times second letter (minus 65)
        return ((toupper(word[0]) - 65) + (26 * (toupper(word[1]) - 65)));
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    
    // // I'm 99% sure I ought to fill the dictionary with null pointers first
    // for (int i = 0; i < N; i++)
    // {
    //     table[i]->next = NULL;
    // }
    
    
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char this_word[LENGTH + 1];
    while (fscanf(file, "%s", this_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, this_word);
        dict_size++;
        int this_hash = hash(this_word);
        n->next = table[this_hash];
        // printf("%s -> %i\n", this_word, this_hash);
        table[this_hash] = n;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            node *tmp = trav;
            trav = trav->next;
            free(tmp);
        }
        
    }
    
    return true;
}
