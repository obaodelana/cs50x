// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26 * 26 * 26;
// Overall hash table size
unsigned int tableSize = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *tmp = table[hash(word)];

    while (tmp != NULL)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }

        tmp = tmp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int count = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        count += tolower(word[i]);
        count *= tolower(word[i]);
    }

    return count % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Array to store each word
    char word[45];
    // Open file with words (dictionary)
    FILE *dictionaryFile = fopen(dictionary, "r");
    // Error checking
    if (dictionaryFile == NULL)
    {
        return false;
    }

    // Add new nodes while there are words
    while (fscanf(dictionaryFile, "%s", word) != EOF)
    {
        // New node
        node *n = malloc(sizeof(node));
        // Error checking
        if (n == NULL)
        {
            fclose(dictionaryFile);
            return false;
        }
        // Set word variable to new word in file
        strcpy(n->word, word);
        // Next points to nothing
        n->next = NULL;

        // Get an index from hash function
        int index = hash(word);
        // If the hash table isn't pointing to anything, point to this new node
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        // Else...
        else
        {
            // Point the new node next variable to what the table points to (which is a node)
            n->next = table[index];
            // And point the table to the new node
            table[index] = n;
        }

        // Increment the overall hash table size
        tableSize++;
    }

    // Close the file
    fclose(dictionaryFile);
    // Return true as successful
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return tableSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Temporary pointers
    node *tmp, *cursor;

    // Go through each row
    for (int i = 0; i < N; i++)
    {
        // Set the temporary variables ot the current row in the hash table
        tmp = table[i], cursor = table[i];

        // While the temp variable is not null
        while (tmp != NULL)
        {
            // Set the cursor temp variable to the next node in this row
            cursor = tmp->next;

            // Free the current node
            free(tmp);
            // Set temp variable to next node
            tmp = cursor;
        }
    }

    return true;
}
