// Implements a dictionary's functionality
#include <stdbool.h>
#include "dictionary.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Initialize the counter for size of dictionary
int SIZE_LENGTH = 0;

// TODO: Choose number of buckets in hash table
// Large number of buckets because the hash function is a sum 
const unsigned int N = 500;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // Hash word to obtain hash value
    int hash_value = hash(word);
    
    //Access linked list at that index in the hash table
    node *cursor = table[hash_value];

    // Traverse linked list and look for the word
    while (cursor != NULL)
    {
        // Check if the case insensitive words match
        if (strcasecmp(word, cursor->word) != 0)
        {
            cursor = cursor->next;
        }
        // If no, move cursor to the next node
        return true;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    
    // Counter
    long hash_sum = 0;
    int L = strlen(word);

    // A hash function that sums the value of char (uppercase) in a word
    for (int i = 0; i < L; i++)
    {
        hash_sum += toupper(word[i]);
    }

    // Make sure that hash value is in the valid range
    return hash_sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    // TODO
    // Open dictionary file
    FILE *load_dict = fopen(dictionary, "r");

    // Check if return value is null
    if (load_dict == NULL)
    { 
        printf("Could not load dictionary.\n");
        return false;
    }

    // Initialize buffer of longest word length
    char buffer[LENGTH + 1];

    // Read each string from file fscanf
    while (fscanf(load_dict, "%s", buffer) != EOF)
    {
        // Allocate memory
        node *n = malloc(sizeof(node));

        // Check if NULL
        if (n == NULL)
        {
            return false;
        }

        // Copy word
        strcpy(n->word, buffer);
        //set next to NULL

        //Hash word to obtain a hash value 
        int hash_value = hash(buffer);

        // Set new node's pointer
        n->next = table[hash_value];
        // Set table pointer to new node
        table[hash_value] = n;

        // Increment size counter
        SIZE_LENGTH++;

    }

    // Close file
    fclose(load_dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Return the counter for size of dictionary
    return SIZE_LENGTH;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterate through all elements in the array of the hash table
    for (int i = 0; i < N; i++)
    {
        // Initialize cursor 
        node *cursor = table[i];

        // Loop through the linked list 
        while (cursor != NULL)
        {
            /// Make temp to track the current node
            node *temp = cursor;
            // Move cursor to the next node
            cursor = cursor->next;
            // Free temp
            free(temp);
        }
    }
    return true;
}
