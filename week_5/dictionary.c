// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// here we include necessary prototypes
unsigned int hash_helper(const char *word, int i, unsigned int ascii);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Word_count of the dictionary;
int WORD_COUNT = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // return false;
    node *current = table[hash(word)];
    for (node *ptr = current; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    return hash_helper(word, 0, 1);
}

unsigned int hash_helper(const char *word, int i, unsigned int ascii)
{
    if (!word[i])
    {
        return ascii % 26;
    }
    int tmp = toupper(word[i]) - 'A';
    ascii = ascii * (3 * tmp) + tmp;
    i++;
    return hash_helper(word, i, ascii);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Read each word in the file
    char *tmp = malloc((LENGTH + 1) * sizeof(char));
    if (tmp == NULL)
    {
        return false;
    }
    while (fscanf(source, "%s", tmp) != EOF)
    {
        node *new = malloc(sizeof(node));
        if (new == NULL)
        {
            return false;
        }
        strcpy(new->word, tmp);
        new->next = NULL;

        int hash_code = hash(tmp);
        new->next = table[hash_code];
        table[hash_code] = new;
        WORD_COUNT++;
    }

    // here we free the tmp and the new memory;
    free(tmp);
    // Close the file;
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return WORD_COUNT;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // return false;
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        if (i == N - 1 && ptr == NULL)
        {
            return true;
        }
    }
    return false;
}
