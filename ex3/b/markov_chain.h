#ifndef _MARKOV_CHAIN_H
#define _MARKOV_CHAIN_H

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool

#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate new"\
" memory\n"
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

/***************************/
typedef void (*print_f) (void *);
typedef int (*comp_f) (void *, void *);
typedef void (*free_data_f) (void *);
typedef void* (*copy_f) (void *);
typedef bool (*is_last_func) (void *);
/***************************/


/***************************/



/***************************/
/*        STRUCTS          */
/***************************/

typedef struct MarkovNode {
    /**
     * this struct describes the vertices on a Markov chain
     */
    //point to word
//    char *data;
    void* data;
//    int size;
    //point to dynamic array of MarkovNodeFrequency's (all words that appear
    // after data, and number of times).
    //don't forget to free this memory.
    //if this word ends a sentence, this will point to NULL.
    struct MarkovNodeFrequency* frequencies_list;
//     struct MarkovNodeFrequency* frequencies_list_end;
    int list_size;
//     int capacity;
} MarkovNode;

typedef struct MarkovNodeFrequency {
    struct MarkovNode * markov_node;
    int frequency;
} MarkovNodeFrequency;

/* DO NOT ADD or CHANGE variable names in this struct */
typedef struct MarkovChain {
    LinkedList *database;

    // pointer to a func that receives data from a generic type and prints it
    // returns void.
    print_f print_func;

    // pointer to a func that gets 2 pointers of generic data type(same one)
    // and compare between them */
    // returns: - a positive value if the first is bigger
    //          - a negative value if the second is bigger
    //          - 0 if equal
    comp_f comp_func;

    // a pointer to a function that gets a pointer of generic data type and
    // frees it.
    // returns void.
    free_data_f free_data;

    // a pointer to a function that  gets a pointer of generic data type and
    // returns a newly allocated copy of it

    // returns a generic pointer.
    copy_f copy_func;

    //  a pointer to function that gets a pointer of generic data type
    //  and returns:
    //      - true if it's the last state.
    //      - false otherwise.
    is_last_func is_last;
} MarkovChain;

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
 * @param first_node markov_node to start with, if NULL- choose a
 * random markov_node
 * @param  max_length maximum length of chain to generate
 */

void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_database(MarkovChain **markov_chain);

/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @param markov_chain
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */

bool add_node_to_frequencies_list(MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr);

/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return node wrapping given data_ptr in given chain's database
 */

void free_markov_node(MarkovNode *mark_node, free_data_f free_data);
MarkovChain* init_chain(free_data_f free_d, comp_f comp, copy_f
copy_d, print_f print_d, is_last_func my_last);
Node * add_to_database(MarkovChain *markov_chain, void *data_ptr);
bool init_freq_list(MarkovNode *first_node, MarkovNode *second_node);
void free_linked_list(LinkedList *linked_list, free_data_f free_data);
void free_node(Node* node, free_data_f free_markovnode);
MarkovNode *init_markovenode(void * ptr, copy_f copy);
void free_chain(MarkovChain* markov_chain);

#endif /* _MARKOV_CHAIN_H */
