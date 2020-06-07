// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

//Counter for number of words
unsigned int SIZE = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Hash the word to find where it should be indexed on the hash table
    int wordLoc = hash(word);

    //Loop through the nodes at the appropriate index to find out if the word is there
    for (node *cursor = table[wordLoc]; cursor != NULL; cursor = cursor->next)
    {
        //If the word is there, return true
        if (strcasecmp((cursor->word), word) == 0)
        {
            //printf("Found\n");
            return true;
        }
    }

    //If unable to find the word when looping through, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Use dan bernstein djb2 hash found at http://www.cse.yorku.ca/~oz/hash.html to determine hash
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        c = tolower(c);
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    //Ensure hashed value fits within a bucket
    hash %= N;

    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open up the dictionary file, return false if it fails
    FILE *stream = fopen(dictionary, "r");
    if (stream == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }

    //Create a character array to pull the word into
    char wordToAdd[LENGTH];

    //For each word in the dictionary, until reaching the end, add it to a spot in memory
    while (fscanf(stream, "%s", wordToAdd) != EOF)
    {
        //Create a node for the new word, returning an error if it doesn't work
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }
        strcpy(n->word, wordToAdd);
        n->next = NULL;

        //Hash the new word
        unsigned int wordSpot = hash(wordToAdd);

        //Add the new word to the start of the existing linked list
        n->next = table[wordSpot];
        table[wordSpot] = n;

        //Increment size
        SIZE++;
    }

    //If end is reached, return that the function was successful
    if (fscanf(stream, "%s", wordToAdd) == EOF)
    {
        //printf("Successfully loaded to end of dictionary.\n");
        fclose(stream);
        return true;
    }
    
    fclose(stream);
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (SIZE > 0)
    {
        return SIZE;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Start at the top of the dictionary list, and for each element, free the associated linked list
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        //For each element, loop through the linked list
        while (cursor != NULL)
        {
            //Create a temporary variable, point it at the list element to be freed
            node *tmp = cursor;

            //Increment the cursor
            cursor = cursor->next;

            //Free memory from the temporary variable
            free(tmp);
        }
    }

    return true;
}
