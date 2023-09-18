#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "markov_chain.h"
#include "linked_list.h"
#define MAX_TWEET_LEN 20

int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain);
int ends_with_period(char *str);
MarkovNode * get_ith_element_in_database(MarkovChain* markov_chain, int i);

int main(int argc, char ** argv)
/**
 * @arg1 unsigned int = seed value (assume valid non negative unsigned int)
 * @arg2 int = amount of tweets to create (assume valid positive int)
 * @arg3 string = path to text_corpus file
 * @arg4(optional) int = amount of words to read from text_corpus
 *
 * @param argc
 * @param argv
 * @return
 */
{
    if(argc < MIN_ARGS || argc > MAX_ARGS)
    {
        //not right amount of args
        fprintf(stdout, "Usage: Number of arguments must be 3 or 4!\n");
        return EXIT_FAILURE;
    }
    unsigned int seed = (unsigned) strtol(argv[SEED], NULL, BASE);
    srand(seed);
    //do not assume path *argv[2] is valid
    FILE *text_corpus = fopen(argv[FILE_PATH], "r");
    if(text_corpus == NULL)
    {
        //if not valid print error msg to stdout and return exit_failure
        fprintf(stdout, "ERROR: Invalid path!\n");
        return EXIT_FAILURE;
    }
    MarkovChain *markov_chain = init_chain();
    if(!markov_chain)
    {
        fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    int words_to_count = INT_MAX;
    if(argc == MAX_ARGS)
    {
        words_to_count = (int) strtol(argv[WORDS_TO_COUNT], NULL, BASE);
    }
    if(fill_database(text_corpus, words_to_count, markov_chain) == 0)
    {
        //successful filling of database
        int num_tweets = (int) strtol(argv[NUM_TWEETS], NULL, BASE);
        for(int i=0; i<num_tweets; i++)
        {
            fprintf(stdout, "Tweet %d:", i+1);
            MarkovNode * first_word = get_first_random_node(markov_chain);
            generate_tweet(markov_chain, first_word, MAX_TWEET_LEN);
            fprintf(stdout, "\n");
        }
    }
    else
    {
        fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    free_database(&markov_chain);

}


int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain)
/**
 * This function reads from fp file either all the file of up to the number
 * of words to read and fills the database of type MarkovChain.
 *
 * @param fp
 * @param words_to_read
 * @param markovChain
 * @return EXIT_SUCCESS if database was filled, EXIT_FAILURE if not.
 */
{
    int counter = 0;
    char buffer[BUFFER_SIZE];
    char* word_token = NULL;
    char* word_delim = " \n\r";
    Node* prev = NULL;

    //iterate by sentence
    while(fgets(buffer, MAX_ROW_LEN, fp))
    {
        word_token = strtok(buffer, word_delim);
        while(word_token && counter<words_to_read)
        {
            counter++;
            Node *added = add_to_database(markov_chain, word_token);
            if (!added)
            {
                fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
                return EXIT_FAILURE;
            }
            if (prev)
                //if not first word in database
            {
                if (!add_node_to_frequencies_list(prev->data, added->data) ==
                    true)
                {
                    free_database(&markov_chain);
                    fprintf(stdout, ALLOCATION_ERROR_MASSAGE);
                    return EXIT_FAILURE;
                }
            }
            if(ends_with_period(word_token))
            {
                prev = NULL;
            }
            else
            {
                prev = added;
            }
            word_token = strtok(NULL, word_delim);
        }
    }
    return EXIT_SUCCESS;
}

int ends_with_period(char *str)
{
    // Get a pointer to the last character in the string
    char *last_char = strchr(str, '\0') - 1;
    if (*last_char == '.')
    {
        // String ends with a period
        return true;
    }
    else
    {
        // String does not end with a period
        return false;
    }
}



/**
* get random number between 0 and max_number [0, max_number].
 * @param max_number maximal number to return (not including)
 * @return Random number
*/
int get_random_number(int max_number)
{
    return rand() % (max_number);
}

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
    while(true)
    {
        int i = get_random_number(markov_chain->database->size);
        MarkovNode * element_i = get_ith_element_in_database(markov_chain, i);
        if(!ends_with_period(element_i->data))
        {
            return element_i;
        }
    }
}

MarkovNode * get_ith_element_in_database(MarkovChain* markov_chain, int i)
{
    Node * cur = markov_chain->database->first;
    //j=i
    for(int j=0;j<i;j++)
    {
        cur = cur->next;
    }
    return cur->data;
}

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr)
{
    int cur_element = 0;
    int freq_sum = 0;
    for(int k=0; k<state_struct_ptr->list_size; k++)
    {
        freq_sum += state_struct_ptr->frequencies_list[k].frequency;
    }
    int i = get_random_number(freq_sum);
    int freqs = 0;
    for(int j=0;j<state_struct_ptr->list_size; j++)
    {

        if(i<freqs)
        {
            return state_struct_ptr->frequencies_list[cur_element].markov_node;
        }
        freqs += state_struct_ptr->frequencies_list[j].frequency;
        cur_element = j;
    }
    return state_struct_ptr->frequencies_list[cur_element].markov_node;
}

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_tweet(MarkovChain *markov_chain,
                      MarkovNode *first_node, int max_length)
{
    if(first_node == NULL)
    {
        first_node = get_first_random_node(markov_chain);
    }
    int counter = 1;
    fprintf(stdout, " %s", first_node->data);
    while(counter<max_length && !ends_with_period(first_node->data))
    {
        first_node = get_next_random_node(first_node);
        fprintf(stdout, " %s", first_node->data);
//        if(ends_with_period(first_node->data))
//        {
//            return;
//        }
        counter++;
    }
}