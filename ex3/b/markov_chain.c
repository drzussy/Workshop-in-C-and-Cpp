
#include <stdlib.h>
#include <string.h>
#include "markov_chain.h"
#include "linked_list.h"


/**
 * function signatures
 */
//#define DEF MEM_ALLOC_ERROR


/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */


Node* add_to_database(MarkovChain *markov_chain, void *data_ptr)
{
    if(!markov_chain || !data_ptr)
    {
        return NULL;
    }
    //check if word is in database
    Node *query = NULL;
    query = get_node_from_database(markov_chain, data_ptr);
    if(query)
    {
        return query;
    }
    //add node to markov_chain
    MarkovNode* markov_node = init_markovenode(data_ptr,
                                              markov_chain->copy_func);
    if(markov_node)
    {
        if(add(markov_chain->database, markov_node) == 0)
        {
                return markov_chain->database->last;
        }
        markov_chain->free_data(markov_node);
    }

//   //didn't manage to add then free
//   free_node(markov_chain->database->last, markov_chain->free_data);

//   //what am i doing here?
//   Node*temp = markov_chain->database->first;
//   for(int i=0;i<markov_chain->database->size-2;i++)
//   {
//       temp=temp->next;
//   }
//   markov_chain->database->last = temp;
   return NULL;
}

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */

Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr)
{
    if (markov_chain && data_ptr && markov_chain->database)
    {
        //iterate over markov_chain to find Markov_Node that contains data_ptr
        Node *cur = markov_chain->database->first;
        while (cur && cur->data  && cur->data->data)
        {
            if (!markov_chain->comp_func(cur->data->data, data_ptr))
            {
                //if found return MarkovNode ptr
                return cur;
            }
            else
            {
                cur = cur->next;
            }
        }
    }
    //not found - return NULL
    return NULL;
}


MarkovNodeFrequency *find_data_in_freq_list(MarkovNode *first_node,
                                              MarkovNode
*second_node, comp_f comp)
{
    for(int i=0;i<first_node->list_size;i++)
        {
        if(!comp(first_node->frequencies_list[i].markov_node->data,
                   second_node->data))
        {
            first_node->frequencies_list[i].frequency++;
            return &(first_node->frequencies_list[i]);
        }
    }
    return NULL;
}

/**
 * Add the second markov_node to the frequency list of the first markov_node.
 * If already in list, update it's occurrence frequency value.
 * @param first_node
 * @param second_node
 * @return pointer to markovnodefrequency struct
 */

bool add_data_to_freq_list(MarkovNode *first_node, MarkovNode
*second_node)
{
    //if not, realloc and update data
    MarkovNodeFrequency * temp = first_node->frequencies_list;
    temp = realloc(temp, ((first_node->list_size)+1)*sizeof
    (MarkovNodeFrequency));
    if(!temp)
    {
        return false;
    }
    first_node->frequencies_list = temp;
    first_node->frequencies_list[first_node->list_size].markov_node =
            second_node;
    first_node->frequencies_list[first_node->list_size].frequency = 1;
    first_node->list_size++;
    return true;
}

bool add_node_to_frequencies_list(MarkovNode *first_node,
                                  MarkovNode *second_node, MarkovChain
                                  *markov_chain)
/**
 * This function add node to freq list and updates relevant data fields 
 * (list_size in first_node, freq_list in first node).
 * @param first_node word1
 * @param second_node word2 (after word1), word being counted.
 * @return true if successful, false if not (memory alloc issues)
 */
{
    // if first word to follow then begin dynamic array
    if(!first_node->frequencies_list)
    {
        return init_freq_list(first_node, second_node);
    }
    MarkovNodeFrequency* data =
            find_data_in_freq_list(first_node,second_node,
                                   markov_chain->comp_func);
    if(!data)//word not in list, add to list
    {
        return add_data_to_freq_list(first_node, second_node);
    }
    else
    //word in list, update freq++ and return true;
    {
        //word->frequency++;
        return true;
    }
}

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_database(MarkovChain ** ptr_chain)
{
    free_chain(*ptr_chain);
    *ptr_chain = NULL;
}



MarkovChain * init_chain(free_data_f free_d, comp_f comp, copy_f
copy_d, print_f print_d, is_last_func my_last)
/**
 * initialize a markov chain struct and its database (linkedlist).
 * set first, last to null and size to 0.
 * @return  pointer to markov_chain
 */
{
    MarkovChain *markov_chain = malloc(sizeof(MarkovChain));
    if(markov_chain)
    {
        markov_chain->free_data = free_d;
        markov_chain->comp_func =comp;
        markov_chain->copy_func = copy_d;
        markov_chain->is_last = my_last;
        markov_chain->print_func= print_d;
        markov_chain->database = malloc(sizeof(LinkedList));
        if(markov_chain->database)
        {
            markov_chain->database->first = NULL;
            markov_chain->database->last = NULL;
            markov_chain->database->size = 0;
            return markov_chain;
        }
        free(markov_chain);
        markov_chain = NULL;
    }
    return markov_chain;
}

//
void free_chain(MarkovChain* markov_chain)
/**
 * begin process of freeing chain.
 * calls free_linked_list to free database.
 * @param markov_chain
 */
{
    if (markov_chain)
    {
        free_linked_list((markov_chain->database),
                         markov_chain->free_data);
        free(markov_chain);
        markov_chain = NULL;
        return;
    }
}

void free_linked_list(LinkedList *linked_list, free_data_f free_markovchain)
/**
 *  free a linked list.
 * iterates through all nodes and frees them one by one.
 * @param linked_list
 */
{
    if(linked_list)
    {
        Node *head = linked_list->first;
        while (head)
        {
            Node *temp = head->next;
            free_node(head, free_markovchain);
            head = temp;
        }
        free(linked_list);
        linked_list = NULL;
    }
}

void free_node(Node* node, free_data_f free_data)
/**
 * frees a Node struct and its fields
 * @param node
 * @param free_markovnode free function given by the user. recieve a *void
 * and free data in given location according to api
 *
 */
{
    if(node)
    {
        free_markov_node(node->data, free_data);
        free(node);
        node = NULL;
        return;
    }
}
//

void free_markov_node(MarkovNode *mark_node, free_data_f free_data)
/**
 * frees a MarkovNode and its fields
 * @param mark_node
 */
{
    if(mark_node)
    {
        if(mark_node->frequencies_list)
        {
            free(mark_node->frequencies_list);
            mark_node->frequencies_list = NULL;
            mark_node->list_size = 0;
        }
        if(mark_node->data)
        {
            //call users data to free markov_nodes data (generic)
            free_data(mark_node->data);
        }
        free(mark_node);
    }
}

MarkovNode * init_markovenode(void* ptr, copy_f copy)
/**
 * Initialize a markovnode with data = pointer, rest of fields are set to
 * default settings
 * @param node
 * @param ptr generic data
 * @param copy_f copy function supplied by user to deep copy data
// * @param free_data_f free function suplied by user to free data
 * @return exit_success if successfully allocated, else exit_failure
 */
{
    MarkovNode *mark_node = malloc(sizeof (MarkovNode));
    if(!mark_node)
    {
        return NULL;
    }

    mark_node->data = copy(ptr);
    if (mark_node->data)
    {
        mark_node->list_size = 0;
        mark_node->frequencies_list = NULL;
        return mark_node;
    }
    else
    {
        free(mark_node);
        return NULL;
    }
}
bool init_freq_list(MarkovNode *first_node, MarkovNode *second_node)
/**
 * This function initializes a dynamic array for freq_list,
 * assuming no list exists already.
 * @param first_node data 1
 * @param second_node data2 that appears after data1 and is being counted
 * @return true if successfully initialized
 */
{
//    first_node->frequencies_list = malloc(sizeof(MarkovNodeFrequency *));
    first_node->frequencies_list = malloc(sizeof(MarkovNodeFrequency));
    if (first_node->frequencies_list)
    {
        first_node->frequencies_list[0].markov_node = second_node;
        first_node->frequencies_list[0].frequency = 1;
        first_node->list_size = 1;
        return true;
//            first_node->capacity = 1;
    }
    else
    {
        free(first_node->frequencies_list);
        return false;
    }

}


void generate_tweet(MarkovChain *markov_chain, MarkovNode *first_node,
                    int max_length)
{
    if(first_node == NULL)
    {
        first_node = get_first_random_node(markov_chain);
    }
    int counter = 1;
    markov_chain->print_func(first_node->data);
    while(counter<max_length && !markov_chain->is_last(first_node->data))
    {
        first_node = get_next_random_node(first_node);
        markov_chain->print_func(first_node->data);
        counter++;
    }
}
/**
* get random number between 0 and max_number [0, max_number].
 * @param max_number maximal number to return (not including)
 * @return Random number
*/
static int get_random_number(int max_number)
{
    return rand() % (max_number);
}

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

static MarkovNode * get_ith_element_in_database(MarkovChain* markov_chain,
                                                int i)
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
        if(!markov_chain->is_last(element_i->data))
        {
            return element_i;
        }
    }
}



