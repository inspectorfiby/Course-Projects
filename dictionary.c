/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int count = 0;

// node data structure
typedef struct node 
{
    bool is_word;
    struct node *children[27];
} 
    node;
node root = {false,{NULL}};

// create a function to calculate index
int number(char c)
{
    int index;
    if (c == '\'')
        index = 26;
    else
        index = tolower(c) - 'a';
    return index;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* ptr = &root;
    for (int i = 0; i < strlen(word); i++)
    {
        if (ptr -> children[number(word[i])] == NULL)
            return false;
        ptr = ptr -> children[number(word[i])];
    }
    if (ptr -> is_word)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    
    if (fp == NULL)
        return false;
    
    while (!feof(fp))
    {
        char word[LENGTH + 1] = {};
        fscanf(fp, "%s\n", word);
        count++;
        
        node* ptr = &root;
        
        for (int i = 0; i < strlen(word); i++) // for every letter in the word
        {
            if (ptr -> children[number(word[i])] == NULL) // if the branch node doesn't already exist
            {
                node *new = malloc(sizeof(node));   
                ptr -> children[number(word[i])] = new;
                ptr = new;
            }
            else
            {
                ptr = ptr -> children[number(word[i])];
            }
        }
        ptr -> is_word = true;
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

// The recursive function to free all nodes under a trie
void free_node(node *ptr)
{
    for (int i = 0; i < 27; i++)
    {
        if (ptr -> children[i] != NULL)
            free_node(ptr -> children[i]);
    }
    free(ptr);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < 27; i++)
    {
        if (root.children[i] != NULL)
            free_node(root.children[i]);
    }
    return true;
}

