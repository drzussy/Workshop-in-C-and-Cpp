#include <stdlib.h>
#include <string.h>
#include "markov_chain.h"
#include "linked_list.h"


/**
 * function signatures
 */
#define DEF MEM_ALLOC_ERROR

//MarkovChain *init_chain();
//void free_chain(MarkovChain* markov_chain);
//void free_linked_list(LinkedList * linked_list);
//void free_node(Node* node);
//void free_markov_node(MarkovNode *mark_node);
//void free_markov_node_freq(MarkovNodeFrequency **freq_arr, int *list_size);
//bool init_freq_list(MarkovNode * first_node, MarkovNode * second_node);
//int get_size(char *dataPtr);
//
//int init_markovenode(MarkovNode **node, char* ptr);
int my_add (LinkedList *link_list, void *data);
/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node* add_to_database(MarkovChain *markov_chain, char *data_ptr)
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
//      free_node(query);
        return query;
    }
//    query = malloc(sizeof(Node));
   if (add(markov_chain->database, data_ptr) == 0)
   {
       if (init_markovenode(&(markov_chain->database->last->data),
                            data_ptr) == 0)
       {
           return markov_chain->database->last;
       }
   }
   free_node(markov_chain->database->last);
   Node*temp = markov_chain->database->first;
   for(int i=0;i<markov_chain->database->size-2;i++)
   {
       temp=temp->next;
   }
   markov_chain->database->last = temp;
    return NULL;
}
//query = (int) malloc(sizeof(Node));
// if(query)
// {
// if (init_markovenode(&(query->data), data_ptr) == 0)
// {
// if (!my_add(markov_chain->database, query))
// {
// markov_chain->database->size++;
// }
// else
// {
// free_node(query);
// query = NULL;
// return NULL;
// }
//
// }
// else
// {
// free_node(query);
// }
// }
// return markov_chain->database->last;

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */

Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr)
{
    if (markov_chain && data_ptr && markov_chain->database)
    {
        //iterate over markov_chain to find Markov_Node that contains data_ptr
        Node *cur = markov_chain->database->first;
        while (cur != NULL && cur->data != NULL && cur->data->data)
        {
            if (!strcmp(cur->data->data, data_ptr))
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

MarkovNodeFrequency *find_word_in_freq_list(MarkovNode *first_node, MarkovNode
*second_node)
{
    for(int i=0;i<first_node->list_size;i++)
        {
        if(!strcmp(first_node->frequencies_list[i].markov_node->data,
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

bool add_word_to_freq_list(MarkovNode *first_node, MarkovNode *second_node)
{
    //check if word already in list
//    if(find_word_in_freq_list(first_node, second_node))
//    {
//        return true;
//    }
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
                                  MarkovNode *second_node)
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
    MarkovNodeFrequency* word = find_word_in_freq_list(first_node,second_node);
    if(!word)//word not in list, add to list
    {
        return add_word_to_freq_list(first_node, second_node);
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
    ptr_chain = NULL;
}


/**
 * find size of a string using a given pointer
 * @param dataPtr pointer to a string
 * @return int size of the string
 */
int get_size(char *dataPtr) {
    int counter = 0;
    while(*dataPtr)
    {
        counter++;
        dataPtr++;
    }
    return counter+1;
}


MarkovChain *init_chain()
/**
 * initialize a markov chain struct and its database (linkedlist).
 * set first, last to null and size to 0.
 * @return  pointer to markov_chain
 */
{
    MarkovChain *markov_chain = malloc(sizeof(MarkovChain));
    if(markov_chain)
    {
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

void free_chain(MarkovChain* markov_chain)
/**
 * begin process of freeing chain.
 * calls free_linked_list to free database.
 * @param markov_chain
 */
{
    if (markov_chain)
    {
        free_linked_list((markov_chain->database));
        free(markov_chain);
        markov_chain = NULL;

        return;
    }
}

void free_linked_list(LinkedList *linked_list)
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
            free_node(head);
            head = temp;
        }
        free(linked_list);
        linked_list = NULL;
    }
}

void free_node(Node* node)
/**
 * frees a Node struct and its fields
 * @param node
 */
{
    if(node)
    {
        free_markov_node(node->data);
        free(node);
        node = NULL;
        return;
    }
}

void free_markov_node(MarkovNode *mark_node)
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
        if(mark_node->data && mark_node->size !=0)
        {
            free(mark_node->data);
            mark_node->size = 0;
        }
        free(mark_node);
    }
}

int init_markovenode(MarkovNode **node, char* ptr)
/**
 * Initialize a markovnode with data = pointer, rest of fields are set to
 * default settings
 * @param node
 * @param ptr string to add
 * @return
 */
{
    *node = malloc(sizeof (MarkovNode));
    if(!(*node))
    {
        return EXIT_FAILURE;
    }


    (*node)->size = get_size(ptr);
    (*node)->data = malloc((*node)->size);
    if ((*node)->data)
    {
        strcpy((*node)->data, ptr);
        (*node)->list_size = 0;
        (*node)->frequencies_list = NULL;
        return EXIT_SUCCESS;
    }
    else
    {
        free_markov_node(*node);
        return EXIT_FAILURE;
    }
}
bool init_freq_list(MarkovNode *first_node, MarkovNode *second_node)
/**
 * This function initializes a dynamic array for freq_list,
 * assuming no list exists already.
 * @param first_node word1
 * @param second_node word2 that appears after word1 and is being counted
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

int my_add (LinkedList *link_list, void *data)
{
    //if first_node
    if(link_list->first)
    {
        link_list->last->next = data;
        link_list->last = data;
    }

    else
    {
        link_list->first = data;
        link_list->last = link_list->first;
    }
    link_list->last->next = NULL;
    return EXIT_SUCCESS;
}


