
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "markov_chain.h"
#include "linked_list.h"
#define MAX_TWEET_LEN 20


static int get_size(char *dataPtr);
static int fill_database(FILE *fp, int words_to_read,
                         MarkovChain *markov_chain);
//static int ends_with_period(char *str);
//static MarkovNode * get_ith_element_in_database(MarkovChain* markov_chain,
// int i);
static void * my_cpy(void* ptr);
void print_data(void* data);
static int my_cmp(void * data1, void* data2);
void free_data(void* data);
bool my_last(void* data);
int ends_with_period(char *str);


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
    MarkovChain *markov_chain = init_chain(free_data, my_cmp, my_cpy,
                                           print_data, my_last);
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
            fprintf(stdout, "Tweet %d: ", i+1);
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
    return EXIT_SUCCESS;
}


static int fill_database(FILE *fp, int words_to_read, MarkovChain
*markov_chain)
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
                if (!add_node_to_frequencies_list(prev->data, added->data,
                                                  markov_chain) == true)

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





/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */




/**
 * find size of a string using a given pointer
 * @param dataPtr pointer to a string
 * @return int size of the string
 */
static int get_size(char *dataPtr) {
    int counter = 0;
    while(*dataPtr)
    {
        counter++;
        dataPtr++;
    }
    return counter+1;
}

void * my_cpy(void* ptr)
{
    if(!ptr)
    {
        return NULL;
    }
    char* data = (char*) ptr;
    int size = get_size(data);
    char* new_copy = malloc(size);
    if(new_copy)
    {
        strcpy(new_copy, data);
    }
    return new_copy;
}

void free_data(void* data)
{
    free((char*) data);
}

void print_data(void* data)
{

//    char* string = ((MarkovNode*)data)->data;
    char* string = data;
    if(ends_with_period(string))
    {
        fprintf(stdout, "%s", string);
    }
    else
    {
        fprintf(stdout, "%s ", string);
    }
}

static int my_cmp(void * data1, void* data2)
{
    return strcmp((char*)data1, (char*)data2);
}

int ends_with_period(char *str)
{
    // Get a pointer to the last character in the string
    char *last_char = strchr(str, '\0') - 1;
//    char *last_char = strchr(str, '\0');
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


bool my_last(void *data)
{
    // Get a pointer to the last character in the string
    return ends_with_period((char*)data);
}


