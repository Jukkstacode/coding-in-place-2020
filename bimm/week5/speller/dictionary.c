// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

#define HASHTABLE_SIZE 1000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *hashtable[N];

unsigned int num_words = 0;
bool is_loaded = false;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char check_word[strlen(word)];
    strcpy(check_word, word);
    for (int i = 0; check_word[i] != '\0'; i++)
    {
        check_word[i] = tolower(check_word[i]);
    }
    int index = hash(check_word);
    if (hashtable[index] != NULL)
    {
        for (node *nodeptr = hashtable[index]; nodeptr != NULL; nodeptr = nodeptr->next)
        {
            if (strcmp(nodeptr->word,check_word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
// Hashes word to a number

// Source: djib2 by Dan Bernstein (http://www.cse.yorku.ca/~oz/hash.html)

unsigned long hash = 5381;

int c = *word;

c = tolower(c);

while (*word != 0)

{

hash = ((hash << 5) + hash) + c;

c = *word++;

c = tolower(c);

}

return hash % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *inDict = fopen(dictionary, "r");
    if (inDict == NULL)
    {
        printf("Error opening dictionary\n");
        return 1;
    }
    //Set the hashtable equal to NULL
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }
    node *new_nodeptr;
    char word[LENGTH + 1];
    //read strings from the file one at a time
    while (fscanf(inDict, "%s", word) != EOF)
    {
        num_words++;
        do
        {
            new_nodeptr = malloc(sizeof(node));
            if (new_nodeptr == NULL)
            {
                free(new_nodeptr);
            }
        }
        while (new_nodeptr == NULL);
        strcpy(new_nodeptr->word, word);
        int index = hash(word);
        if (hashtable[index] == NULL)
        {
            new_nodeptr->next = NULL;
            hashtable[index] = new_nodeptr;
        }
        else
        {
            new_nodeptr->next = hashtable[index];
            hashtable[index] = new_nodeptr;
        }
}
    fclose(inDict);
    is_loaded = true;
    return true;
    //create a new node for each word
    //hash the word to obtain a hash value
    //insert node into hash table at that location
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (!is_loaded)
    {
        return false;
    }
    return num_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (!is_loaded)
    {
        return false;
    }
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *ptr = hashtable[i];
        while (ptr != NULL)
        {
            node *preptr = ptr;
            ptr = ptr->next;
            free(preptr);
        }
    }
    return true;
}
