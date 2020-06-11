// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a trie
node *root;

// Count words read globally
int wordcount = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = node_create();

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Create node pointer to traverse trie
    node *trav = NULL;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // wordlen ensures loop doesn't iterate past end of current word
        int wordlen = strlen(word);

        // Point cursor to top of trie
        trav = root;

        // Iterate through letters in read word
        for (int i = 0; i < wordlen; i++)
        {
            // Hash current letter to element index number; false if unsupported char
            int letter;
            if (isalpha(word[i]))
            {
                letter = tolower(word[i]) - 'a';
            }
            else if (word[i] == '\'')
            {
                letter = 26;
            }
            else
            {
                return false;
            }

            // Check if the specified child index at this point in trie is NULL
            if (trav->children[letter] == NULL)
            {
                // If NULL, malloc new node at that child element so it is != NULL
                trav->children[letter] = node_create();
                if (!trav->children[letter])
                {
                    return 1;
                }
                // Point trav to new node, so next letter searches from there
                trav = trav->children[letter];
            }
            // If a node already exists at this index, point trav at (into) it
            else
            {
                trav = trav->children[letter];
            }
        }
        // Set is_word to true after reaching end of word
        trav->is_word = true;
        wordcount++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Function to create a new node
node *node_create(void)
{
    // Allocate space for new node, return failure if no space availible
    node *new_node = (node *) malloc(sizeof(node));

    if (new_node == NULL)
    {
        return false;
    }

    new_node->is_word = false;

    // Initialize all children to NULL
    for (int i = 0; i < N; i++)
    {
        new_node->children[i] = NULL;
    }

    return new_node;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create node pointer to traverse trie
    node *trav = NULL;

    int wordlen = strlen(word);

    // Start traversal from root
    trav = root;

    for (int i = 0; i < wordlen; i++)
    {
        // Hash current letter to element index number; false if unsupported char
        int letter;
        if (isalpha(word[i]))
        {
            letter = tolower(word[i]) - 'a';
        }
        else if (word[i] == '\'')
        {
            letter = 26;
        }
        else
        {
            return false;
        }

        // Traverse trie until either a NULL ptr or end of word is reached
        if (trav->children[letter] == NULL)
        {
            return false;
        }
        else
        {
            trav = trav->children[letter];
        }
    }
    // If at end of word, check if is_word is marked true
    if (trav->is_word == true)
    {
        return true;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Call recursive function to free all dynamically allocated memory
    trie_free(root);
    return true;
}

void trie_free(node *trie_root)
{
    node *trav = NULL;

    //Begin at root, as passed into function
    trav = trie_root;
    // Cycle through elements of current node->children[]
    for (int i = 0; i < N; i++)
    {
        // If element != NULL, go deeper before incrementing and call function again
        if (trav->children[i] != NULL)
        {
            trie_free(trav->children[i]);
        }
    }
    free(trav);
}