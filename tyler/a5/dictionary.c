// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // printf("Word: %s \n", word);
    char myWord[LENGTH + 1];
    strcpy(myWord,word);
    int strLen = strlen(myWord);
    for (int i = 0; i < strLen; i++)
    {
        if (isupper(myWord[i]))
        {
            myWord[i] = tolower(myWord[i]);
        }
    }
    
    if (table[0] == NULL)
    {
        // printf("Empty\n");
        return false;
    }
    else
    {
        // printf("Not empty\n");
        node *nextPtr = table[0]->next;
        // printf("1\n");
        if (table[0]->next == NULL)
        {
            // printf("2\n");
            if (strcmp(table[0]->word,myWord)==0)
            {
                // printf("Match on only\n");
                return true;
            }
            else
            {
                // printf("No match on only\n");
                return false;
            }
        }
        // printf("Past \n");
        node *prevPtr = table[0];
        if (strcmp(prevPtr->word,myWord)==0)
        {
            return true;
        }
        bool past = false;
        while (nextPtr->next != NULL && !past)
        {
            // printf("in: %s, prev: %s (%d), next: %s (%d)\n", myWord, prevPtr->word, strcmp(prevPtr->word,myWord), nextPtr->word, strcmp(nextPtr->word,myWord));
            if (strcmp(nextPtr->word,myWord)==0)
            {
                return true;
            }
            else if (strcmp(prevPtr->word,myWord)<0 && strcmp(nextPtr->word,myWord)>0)
            {
                // printf("early exit\n");
                return false;
            }
            prevPtr = nextPtr;
            nextPtr = nextPtr->next;
        }
        if (strcmp(nextPtr->word,myWord)==0 || strcmp(prevPtr->word,myWord)==0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    node *lastPtr = { NULL };
    // printf("Start\n");
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        free(lastPtr);
        return false;
    }

    // Prepare to spell-check
    int index = 0, words = 0;
    char word[LENGTH + 1];

    // Spell-check each word in text
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while ((c = fgetc(file)) != EOF && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(file)) != EOF && isalnum(c));

            // Prepare for new word
            index = 0;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';
            // printf("word: %s\n",word);

            // int key = tolower(word[0]) - 'a'

            node *newPtr = malloc(sizeof(node));
            if (newPtr == NULL)
            {
                fprintf(stderr, "Not enough memory to store image.\n");
                unload();
                return false;
            }
            newPtr->next = NULL;
            strcpy(newPtr->word,word);

            if (table[0] == NULL)
            {
                // printf("NewPtr\n");
                table[0] = newPtr;
                lastPtr = newPtr;
            }
            else
            {
                // printf("ToTail\n");
                // node *prevPtr = table[0];
                // while(prevPtr->next != NULL)
                // {
                //     prevPtr = prevPtr->next;
                // }
                // prevPtr->next = newPtr;
                lastPtr->next = newPtr;
                lastPtr = newPtr;
            }
            

            // Update counter
            words++;
            // printf("Words: %d\n",words);


            // Prepare for next word
            index = 0;
        }
    }
    // printf("Done1\n");
    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", dictionary);
        unload();
        return false;
    }
    else
    {
        // Close text
        fclose(file);
        // printf("Done\n");
        return true;
    }

    // Close text
    fclose(file);

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // printf("in Size\n");
    int count = 0;
    if (table[0] == NULL)
    {
        return 0;
    }
    else
    {
        node *newPtr = table[0];
        count++;
        while (newPtr->next != NULL)
        {
            count++;
            newPtr = newPtr->next;
        }
    }
    // printf("out size\n");
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // printf("in unload\n");
    if (table[0] == NULL)
    {
        // printf("out unload\n");
        return true;
    }
    else
    {
        node *nextPtr = table[0];
        // node *nextPtr = table[0]->next;
        node *prevPtr = table[0];
        // printf("free: %s\n",prevPtr->word);
        // free(prevPtr);
        
        while (nextPtr->next != NULL)
        {
            prevPtr = nextPtr;
            nextPtr = nextPtr->next;
            // printf("free: %s\n",prevPtr->word);
            free(prevPtr);
        }
        // printf("free: %s\n",nextPtr->word);
        free(nextPtr);
    }
    // printf("out unload2\n");
    return true;
}
