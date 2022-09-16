// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
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
const unsigned int N = 700000;

// Hash table
node *table[N];

// number of words in hash table
unsigned int tableSize = 0;

// prototypes
node *to_list(node *head, char *word);
node *create(char *word);
node *insert(node *head, char *word);
bool find(node *head, const char *word);
void destroy(node **head);


// Returns true if word is in dictionary else false
bool check(const char *word)
{

    // hash the word
    int h = hash(word);

    // check if bucket exists at that index
    if (table[h] != NULL)
    {
        // a linked list exist, check word therein
        return find(table[h], word);
    }

    return false;
}

// Hashes word (converted to lowercase) to a number.
// @param word      word to hash
// @return          hash value
unsigned int hash(const char *word)
// algorithm based on book
// Beginning algorithms, Simon Harris-James Ross
// Wiley Publishing, Inc., Indianapolis, Indiana
{
    int hash = 0;
    int i = 0;
    while (word[i] != '\0')
    {
        hash = 31 * hash + (int) tolower(word[i]);
        i++;
    }

    return (hash % N);
}

// Loads dictionary into memory, returning true if successful else false.
// @param dictionary    path of the dictionary file to load
// @return              true if succesful
bool load(const char *dictionary)
{
    // TODO

    // open dictionary file
    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
    {
        return false;
    }

    //read file line by line
    char w[LENGTH + 1];
    while (fscanf(dictFile, "%s", w) != EOF)
    {
        // hash the word
        int h = hash(w);
        // get pointer to the header of the linked list
        node *n = table[h];
        // put word into the dictionary
        table[h] = to_list(table[h], w);

        // increase word counter
        tableSize++;

    }

    // close dictionary file
    fclose(dictFile);
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
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            destroy(&table[i]);
        }
    }

    return true;
}


/*
 *  Functions to handle linked lists
*/

// Inserts a new node at the beginning of the list, if list exists, otherwise creates a new list.
// @param head      address of head node (NULL, if list doesn't exist yet)
// @param word      word to insert into the new node
// @return          address of the new head node
node *to_list(node *head, char *word)
{
    return (head == NULL) ? create(word) : insert(head, word);
}


// Creates a linked list with one node.
// @param word      word to insert into the new node
// @return          address of the new head node
node *create(char *word)
{
    // allocate memory for the new node
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return n;
    }

    // set node properties
    strcpy(n->word, word);
    n->next = NULL;

    return n;
}

// Inserts a new node at the beginning of the list.
// @param head      address of head node
// @param word      word to insert into the new node
// @return          address of the new head node
node *insert(node *head, char *word)
{
    // allocate memory for the new node
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }

    // set node->word property
    strcpy(n->word, word);

    // insert node at the beginning of list
    n->next = head;
    head = n;

    return head;
}

// Serches the linked list for a given word. Case insensitive!
// @param head      address of head node
// @param word      word to find
// @return          true if word is in the list
bool find(node *head, const char *word)
{
    node *trav = head;

    do
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    while (trav != NULL);

    return false;
}

// Frees memory allocated to the linked list.
// @param head      address of head node
void destroy(node **head)
// based on stackoverflow post
// https://stackoverflow.com/questions/18412620/c-linked-list-destroy-function
{

    if (*head == NULL)
    {
        return;
    }

    destroy(&(*head)->next);

    free(*head);
    *head = NULL;
}