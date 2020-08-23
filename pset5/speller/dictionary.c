// Implements a dictionary's functionality
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

// Number of words in dictionary
int count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int length = strlen(word);
    char new_word[length + 1];
    for (int i = 0, l = length; i < l; i++)
    {
        new_word[i] = tolower(word[i]);
    }
    new_word[length] = '\0';

    int index = hash(new_word);
    node *p = table[index];

    while (p != NULL)
    {
        if (strcasecmp(p->word, new_word) != 0)
        {
            p = p->next;
        }
        else
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    int first;
    int second;

    if (*word - 97 >= 0)
    {
        first = *word - 97;
    }
    else
    {
        first = 0;
    }
    if (*(word + 1) - 97 >= 0)
    {
        second = *(word + 1) - 97;
    }
    else
    {
        second = 0;
    }
    return first * 26 + second;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    // File exist and not empty
    if (!file || file == NULL)
    {
        return false;
    }
    // Read all words from dictionary, allocate memory
    char *word_dict = malloc(sizeof(node));
    if (word_dict == NULL)
    {
        return false;
    }
    while (fscanf(file, "%s", word_dict) != EOF)
    {
        //Create new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, word_dict);
        new_node->next = NULL;
        //Hash word to obtain a hash value
        int hashed = hash(word_dict);
        //Instert node into hash table at this location
        if (table[hashed] == NULL)
        {
            table[hashed] = new_node;
        }
        else
        {
            new_node->next = table[hashed];
            table[hashed] = new_node;
        }
        count++;
    }
    // Close file
    fclose(file);
    free(word_dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}