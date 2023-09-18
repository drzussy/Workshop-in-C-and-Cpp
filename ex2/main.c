#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#define INPUT 1
#define NAME 2
#define TEST 3
#define BAD_PARAM 100
#define MAX_DIST 1000
#define MIN_DIST 0
#define MAX_DURATION 100
#define MIN_DURATION 10
#define BASE 10
#define INPUT_SIZE 21



int sort_type(char** argv, int argc);
long ask_num_lines();
int get_num_lines();
int num_input_check(char num_input[]);
BusLine* build_bus_lines(BusLine * start, int num_lines);
int check_input(char* name, int name_len, int dist, int duration, bool*
printed);
int sort(BusLine *start, BusLine *end, int mode);
void print_array(BusLine* start, BusLine* end);
int run_tests(BusLine* start, BusLine* end);
int valid_mode(int mode);

/**
Receive input from user via command line for desired action. Prompt user for
 desired number of lines. For each line prompt for line information.
 execute desired action.
 actions:
 sort:
 1) by_name
 2) by_distance
 3) by_duration
 for each type of sort print out sorted lines
 test:
 run tests and print to stdout result for each test
 */
int main (int argc, char *argv[])
{
  int mode = sort_type (argv, argc);
  if(mode == BAD_PARAM)
  {
    printf("USAGE: 1 arg: 'by_duration', 'by_distance', 'by_name' or 'test'");
    return EXIT_FAILURE;
  }
  //4 modes by which to run sort_lines
  if(valid_mode(mode))
  {
    //get number of lines
    int num_lines = get_num_lines();
    //build dynamic array of BusLines using num_lines
    BusLine * start = calloc(num_lines * sizeof(BusLine), sizeof(BusLine));
    if(!start)
    {
      printf("ERROR Couldn't allocate dynamic array");
      return EXIT_FAILURE;
    }
    //build specific BusLines by receiving input from user
    BusLine* end = build_bus_lines(start, num_lines);
    //check success of build_BusLines
    if(!end)
    {
      printf ("ERROR Couldn't build BusLines");
      free (start);
      start = NULL;
      return EXIT_FAILURE;
    }
    //run sort, check success of tests
    if(sort(start, end, mode))
    {
      printf("ERROR: couldn't run sorts or test\n");
      return EXIT_FAILURE;
    }
    if(mode!=TEST)
    {
      print_array(start, end);
    }
    free(start);
    start = NULL;
    end = NULL;
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int valid_mode(int mode)
{
  return(mode == DURATION || mode == DISTANCE || mode == NAME || mode == TEST);
}

int sort(BusLine *start, BusLine *end, int mode)
/**
 * sort according to user input
 * */
{
  //sort by mode
  if(mode==NAME)
  {
    bubble_sort (start, end);
    return EXIT_SUCCESS;
  }
  if(mode==DISTANCE || mode==DURATION)
  {
    quick_sort (start, end, mode);
    return EXIT_SUCCESS;
  }
  if(mode==TEST)
  {
    if(run_tests(start, end)){
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}

void print_array(BusLine* start, BusLine* end)
/**
 * prints an array of BusLines.
para: start - pointer to first BusLine
para: end - pointer to last BusLine
 */
{
  //printf("printing\n");
  long array_size = end - start;
  //printf("array size: %li\n", array_size);
  for(int i=0; i<array_size; i++)
  {
    printf("%s,%d,%d\n", (start+i)->name, (start+i)->distance, (start+i)
    ->duration);
  }
  //printf("finished printing\n");
}

BusLine * build_bus_lines(BusLine* start, int num_lines)
/**
 * build BusLines using input from user. return the pointer to the end of the
dynamic array of BusLines
 */
{
  int final = 0;
  //start loop in length of entered amount of lines
  for(int i=0; i<num_lines; i++)
  {
    //for each line create a struct
    int success = 0;
    bool printed = false;
    while(!success)
    {
      printf("Enter line info. Then enter\n");
      //enter line info by required format
      char input[INPUT_SIZE*3+1];
      fgets (input, sizeof (input), stdin);
      char name[INPUT_SIZE], str_dist[INPUT_SIZE], str_duration[INPUT_SIZE];
      //can this handle the last
      success = sscanf (input, "%20[^,],%20[^,],%s", name, str_dist,
                        str_duration);
      int dist = strtol(str_dist, NULL, BASE);
      int duration = strtol(str_duration, NULL, BASE);10
      if (success == 3 && check_input(name, strlen(name), dist, duration,
                                      &printed))
      {
        //build specific BusLine
        strcpy((start+i)->name, name);
        (start+i)->duration = duration;
        (start+i)->distance = dist;
        final = i;
        continue;
      }
      else if(success != 3)
        {
          if(!printed)
          {
            printf ("ERROR bad input, try: '<line_name>,<distance>,"
                    "<duration>'\n");
          }
        }
      success = 0;

    }
  }
    //if `failed return NULL
  //return pointer to one place after last element
    return start + final + 1;
}

int get_num_lines()
/**
 * this function gets num_lines using ask_num_lines, if num_lines is greater
than 0 returns it, otherwise calls ask_num_lines again
 */
{
  while(true)
  {
    int num_lines = ask_num_lines ();
    //if invalid number/format return 0
    //if over 0 then it's a valid number
    if (num_lines > 0)
    {
      return num_lines;
    }
    printf("ERROR: Must be a whole positive number. Try again:\n");

  }
}

int sort_type(char** argv, int argc)
/**
 * returns selected parameter by which to sort bus lines
 * */
{
  if(argc!=2)
  {
    return BAD_PARAM;
  }
  char* param = argv[INPUT];
  if(!strcmp(param, "by_duration")){
    return DURATION;
  }
  else if(!strcmp(param, "by_distance")){
    return DISTANCE;
  }
  else if(!strcmp(param, "by_name")){
    return NAME;
  }
  else if(!strcmp (param, "test")){
    return TEST;
  }
  else //none of the above
  {
    return BAD_PARAM;
  }
}

long ask_num_lines()
/**
 * prompts user for input of number lines and verifies input is whole
positive number. returns number if allowed, otherwise returns 0.
 */
{
  //make the size of num_lines dynamic!!!!
  char num_input[INPUT_SIZE] = {0};
  printf("Enter number of lines. Then enter\n");

  fgets(num_input, sizeof(num_input), stdin);
  //printf("string %s\n", num_input);

  if(num_input_check (num_input) == 0){
    //printf("passed input check\n");

    long num_lines = strtol(num_input, NULL, BASE);
    //printf("%ld long\n", num_lines);

    return num_lines;
  }
  return 0;
}

int num_input_check(char num_input[])
/**
 * checks that input is all numerical
 */
{
  //printf("INT MAX = %d\n", INT_MAX);
  long len_k = strlen(num_input);
  for(int i=0;i<len_k;i++){
    if(i==0 && num_input[0]=='-'){
      i+=1;
    }
    if(!isdigit(num_input[i]) && num_input[i] != '\n'){
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}


BusLine* copy_bus_line(BusLine* start, BusLine* end)
{
  BusLine * start_original = malloc ((end-start)*sizeof(BusLine)+1);
  if(!start_original)
  {
    printf("ERROR: couldn't copy array.\n");
    return NULL;
  }
  memcpy(start_original, start, (end-start)*sizeof(BusLine)+1);
  return start_original;
}

void test_dist(BusLine *start,
               BusLine *end, BusLine *start_original,
               BusLine *end_original)
{
  sort(start,end, DISTANCE);
  //check 1 is_sorted_by_distance
  if(is_sorted_by_distance (start, end))
  {
    printf("TEST 1 PASSED: sorted by distance\n");
  }
  else
  {
    printf("TEST 1 FAILED: not sorted by distance\n");
  }
  //check 2 is_equal
  if(is_equal (start, end, start_original, end_original))
  {
    printf("TEST 2 PASSED: same BusLines\n");
  }
  else
  {
    printf("TEST 2 FAILED: not same BusLines\n");
  }
}

void test_dura(BusLine *start,
               BusLine *end, BusLine *start_original,
               BusLine *end_original)
{
  sort(start,end, DURATION);
  //check 3 is_sorted_by_duration
  if(is_sorted_by_duration(start, end))
  {
    printf("TEST 3 PASSED: sorted by duration\n");
  }
  else
  {
    printf("TEST 3 FAILED: not sorted by duration\n");
  }
  //check 4 is_equal
  if(is_equal (start, end, start_original, end_original))
  {
    printf("TEST 4 PASSED: same BusLines\n");
  }
  else
  {
    printf("TEST 4 FAILED: not same BusLines\n");
  }
}

void test_name(BusLine *start,
               BusLine *end, BusLine *start_original,
               BusLine *end_original)
{
  sort(start,end, NAME);
  //check 5
  if(is_sorted_by_name(start, end))
  {
    printf("TEST 5 PASSED: sorted by name\n");
  }
  else
  {
    printf("TEST 5 FAILED: not sorted by name\n");
  }
  //check 6
  if(is_equal (start, end, start_original, end_original))
  {
    printf("TEST 6 PASSED: same BusLines\n");
  }
  else
  {
    printf("TEST 6 FAILED: not same BusLines\n");
  }
}

int run_tests(BusLine* start, BusLine* end)
/**
 * runs required tests and returns true if passed all
 */
{
  //copy original array
  BusLine * start_original = copy_bus_line (start, end);
  if(!start_original)
  {
    return EXIT_FAILURE;
  }
  // after each test print to stdout TEST 'i' PASSED/FAILED
  BusLine * end_original = start_original + (end-start);
  //quick_sort by DISTANCE
  test_dist (start, end, start_original, end_original);
  //quick_sort by DURATION
  test_dura (start, end, start_original, end_original);
  //bubble sort by name
  test_name(start, end, start_original, end_original);

  free(start_original);
  return EXIT_SUCCESS;
}

int check_name(const char* name, int name_len)
/**
 * checks that input name is lower-alpha or numerical
 */
{
  for(int i=0; i<name_len; i++)
  {
    if(!(islower(name[i]) || isdigit(name[i])))
    {
      return false;
    }
  }
  return true;
}

int check_parameter(int parameter, int lower, int upper)
/**
 * checks given parameter is within allowed limits
 */
{
  return lower <= parameter && parameter <= upper;
}

int check_input(char* name, int name_len, int dist, int duration, bool*
printed)
/**
 * check user input for a BusLine is allowed, gives error for each field and
returns false, if all good returns true.
 */
{
  if(!check_name(name, name_len)){
    printf("ERROR invalid name, must contain only [a,z]U[0,9]\n");
    return false;
  }
  //distance is [0, 1000]
  if(!check_parameter(dist, MIN_DIST, MAX_DIST)){
    printf("ERROR: invalid distance, must be in range [0, 1000]\n");
    *printed = true;
    return false;
  }
  //duration is [10,100]
  if(!check_parameter(duration, MIN_DURATION,MAX_DURATION)){
    printf("ERROR: invalid duration, must be in range [10, 100]\n");
    *printed = true;
    return false;
  }
  return true;
}

