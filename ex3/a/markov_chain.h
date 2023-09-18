#ifndef _MARKOV_CHAIN_H_
#define _MARKOV_CHAIN_H_

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool

#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate"\
            "new memory\n"


#define SEED 1
#define BASE 10
#define FILE_PATH 3
#define MIN_ARGS 4
#define MAX_ARGS 5
#define NUM_TWEETS 2
#define WORD_TO_COUNT 4
#define WORDS_TO_COUNT WORD_TO_COUNT
#define BUFFER_SIZE 1001
#define MAX_ROW_LEN 1001
/**
 * insert Structs here
 */

 typedef struct MarkovChain {
     /**
      * data struct that describes a markovchain model that will be used to
      * creat tweets.
      * contains a linkedlist of nodes who's data is markovnodes
      * */
     //point to a linked list that contains all unique words in text, as
     // pointers to variables of type MarkovNodes.
     struct LinkedList* database;
 } MarkovChain;

 typedef struct MarkovNode{
     /**
      * this struct describes the vertices on a Markov chain
      */
     //point to word
     char *data;
     int size;
     //point to dynamic array of MarkovNodeFrequency's (all words that appear
     // after data, and number of times).
     //don't forget to free this memory.
     //if this word ends a sentence, this will point to NULL.
     struct MarkovNodeFrequency* frequencies_list;
//     struct MarkovNodeFrequency* frequencies_list_end;
     int list_size;
//     int capacity;
 } MarkovNode;

typedef struct MarkovNodeFrequency{
    /**
     * describes the frequency of word2 after word1. relevant only if word2
     * appears after word1.
     * */
    //pointer to vertex of word2
    struct MarkovNode * markov_node;
    //count number of times word2 appears right after word1
    int frequency;
} MarkovNodeFrequency;


/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node* add_to_database(MarkovChain *markov_chain, char *data_ptr);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping it
 * in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr);

/**
 * Add the second markov_node to the frequency list of the first markov_node.
 * If already in list, update it's occurrence frequency value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_frequencies_list(MarkovNode *first_node, MarkovNode
*second_node);


/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_database(MarkovChain ** ptr_chain);

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode* get_first_random_node(MarkovChain *markov_chain);

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr);

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

MarkovChain *init_chain();
void free_chain(MarkovChain* markov_chain);
void free_linked_list(LinkedList * linked_list);
void free_node(Node* node);
void free_markov_node(MarkovNode *mark_node);
bool init_freq_list(MarkovNode * first_node, MarkovNode * second_node);
int get_size(char *dataPtr);
MarkovNodeFrequency *find_word_in_freq_list(MarkovNode *first_node, MarkovNode
*second_node);
bool add_word_to_freq_list(MarkovNode *first_node, MarkovNode *second_node);
int init_markovenode(MarkovNode **node, char* ptr);
#endif /* _MARKOV_CHAIN_H_ */
