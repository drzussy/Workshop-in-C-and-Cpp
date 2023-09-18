
#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20

#define LAST_CELL 100

void my_print(void* data);
static int my_comp(void* data1, void* data2);
static void* my_copy(void* data);
void my_free(void* data);
static bool last(void* data);

/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */

const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder
    // in case there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in
    // case there is one from this square both ladder_to and snake_to should
    // be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_database(database);
    }
    return EXIT_FAILURE;
}


static int create_board(Cell *cells[BOARD_SIZE])
{
    //iterate over all cells and initialize them
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        //if mem_alloc error then free all cells that have already
        // initialized and allocated
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            //send error message
            handle_error(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        //initialize default fields
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }
    //after initializing the board start spreading chutes and ladders from
    // transitions bank onto the board.
    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database(MarkovChain *markov_chain)
{
    //create a one-dimensional array to represent a two-dimensional board
    Cell* cells[BOARD_SIZE];
    //create board
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database(markov_chain, cells[i]);
    }
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,cells[i])->data;
        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain,
                                             cells[index_to])->data;
            add_node_to_frequencies_list (from_node,
                                          to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain,
                                                 cells[index_to])->data;
                add_node_to_frequencies_list (from_node,
                                              to_node, markov_chain);
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stdout, "Usage: Number of arguments must be 3!\n");
        return EXIT_FAILURE;
    }
    srand(strtol(argv[1], NULL, BASE));
    int num_routes = (int)strtol(argv[2], NULL, BASE);
    MarkovChain *markov_chain = init_chain(my_free, my_comp
                                           ,my_copy,my_print, last);
    if(!markov_chain)
    {
        handle_error("ERROR: could not create Chain.\n" ,&markov_chain);
        return EXIT_FAILURE;
    }
    //create board in a markov chain
    if(fill_database(markov_chain) == EXIT_SUCCESS)
    {
        MarkovNode* first_mark_node = markov_chain->database->first->data;
        for(int i=0;i<num_routes;i++)
        {
            //create the ith path using a random number generator and board
            //in markov chain
            printf("Random Walk %d: ", i+1);

            generate_tweet(markov_chain, first_mark_node,
                           MAX_GENERATION_LENGTH);
            printf("\n");
        }
    }
    else
    {
        handle_error("ERROR: Could not fill database.\n",
                     &markov_chain);
        free_chain(markov_chain);
        return EXIT_FAILURE;
    }
    free_chain(markov_chain);
    return EXIT_SUCCESS;
}

//my_funcs
/**
 * print cell numbers, snakes and ladders in format.
 * @param data pointer to a Cell struct
 */
void my_print(void* data)
{
    Cell* cur_cell = (Cell*)(data);
    if(cur_cell->snake_to > 0)
    {
        printf("[%d]-snake to %d -> ", cur_cell->number,
               cur_cell->snake_to);
    }
    else if(cur_cell->ladder_to > 0)
    {
        printf("[%d]-ladder to %d -> ", cur_cell->number,
               cur_cell->ladder_to);
    }
    else if (cur_cell->number == LAST_CELL)
    {
        printf("[%d]", cur_cell->number);
    }
    else
    {
        printf("[%d] -> ", cur_cell->number);
    }
}

/**
 *
 * @param data generic pointer to a Cell struct
 * allocate a cell and copy
 * @return pointer to a copy of cell
 */
static void* my_copy(void* data)
{
    Cell* src = (Cell*)(data);
    Cell* dest = malloc(sizeof (Cell));
    if(dest)
    {
        dest->number = src->number;
        dest->ladder_to = src->ladder_to;
        dest->snake_to = src->snake_to;
    }
    return dest;
}

/**
 * compare two cell number
 * @param data1
 * @param data2
 * @return 0 if identical, otherwise diff
 */
static int my_comp(void* data1, void* data2)
//compare the cells is two markovnodes
{
    int numbah1 = ((Cell *) data1)->number;
    int numbah2 = ((Cell *) data2)->number;
    return numbah1 - numbah2;
}

/**
 *
 * @param data pointer to a cell to be freed
 */
void my_free(void* data)
{
    free(data);
}

/**
 * check if a given cell is the last on the board.
 * @param data pointer to a Cell struct
 * @return true if last, false if not.
 */
static bool last(void* data)
{
    if(((Cell*)data)->number == LAST_CELL)
    {
        return true;
    }
    return false;
}
