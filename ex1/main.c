#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cipher.h"
#include "tests.h"
#define MAX_LINE 1025
#define ACTION 1
#define IN 3
#define OUT 4
#define K 2
#define ENCODE 100
#define DECODE 101
#define TEST 102
#define BASE 10
//#define IN_FILE 0
//#define OUT_FILE 1


// your code goes here
//function calls
int check_input_size(int argc, char *args[]);
int check_k(char* argv[]);
int k_format_check(char k[]);
long convert_k_to_long(char* s);
int check_action(int argc, char* args[]);
int execute_action(FILE* f_in, FILE* f_out, int check, long k);
int close_file_file(FILE* f_in, FILE* f_out);
int run_tests();
/*
FILE ** open_in_out_files(char **argv);
int check_file_open_fail(FILE *f_in, FILE *f_out);
int check_files_open_failure(FILE**f);
int execute_action_files(FILE** files, int check, long k);
int close_files(FILE** files);*/

int main (int argc, char *argv[])
{
    //checks the CLI to see if matches parameter and
    // if so what action will be taken (test/encode/decode)
  int check = check_input_size (argc - 1, argv);
  if (check == TEST)
  {
    return run_tests();
  }
  else if (check == ENCODE || check == DECODE)
  {
      //checks for legal input of k
    if (!check_k (argv)) {
        //convert k from string to long
        long k = convert_k_to_long(argv[K]);
        FILE *f_in = fopen(argv[IN], "r");
        if (f_in == NULL) {
            fprintf(stderr, "The given file is invalid.\n");
            return EXIT_FAILURE;
        }
        FILE *f_out = fopen(argv[OUT], "w");
        if (f_out == NULL) {
            fclose(f_out);
            fprintf(stderr, "The given file is invalid.\n");
            return EXIT_FAILURE;
        }
        //execute encode/decode and add to out file
        execute_action(f_in, f_out, check, k);
        close_file_file(f_in, f_out);
        return EXIT_SUCCESS;
    }
    }
  //if input was not encode/decode/test

  return EXIT_FAILURE;
}

int check_input_size(int argc, char* args[])
{
  if(argc!=4 && argc!=1){
    fprintf(stderr, "The program receives 1 or 4 arguments only.\n");
    return EXIT_FAILURE;
  }
  return check_action(argc, args);
}

int check_action(int argc, char* args[])
//this function checks what action the user put in the CLI and returns it
{
    if(argc==4){
    if(!strcmp(args[ACTION], "encode"))
    {
      return ENCODE;
    }
    else if(!strcmp(args[ACTION], "decode"))
    {
      return DECODE;
    }
  }
    else if(argc == 1)
  {
    if (!strcmp (args[ACTION], "test"))
    {
      return TEST;
    }
    else
    {
      fprintf (stderr, "Usage: cipher test\n");
      return EXIT_FAILURE;

    }
  }
  fprintf (stderr, "The given command is invalid.\n");
  return EXIT_FAILURE;
}

int check_k(char* argv[])
//check that k is in format, if is then return k in int
{
  char* k = argv[2];
  if(k_format_check(k)){
    fprintf (stderr, "The given shift value is invalid.\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int k_format_check(char k[])
//checks that k is all numerical
{
  long len_k = strlen(k);
  for(int i=0;i<len_k;i++){
    if(i==0 && k[0]=='-'){
        i+=1;
    }
    if(!isdigit(k[i])){
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

long convert_k_to_long(char* s)
//convert k from string to long
{
  long num_k = strtol (s, NULL, BASE);
  return num_k;
}

int close_file_file(FILE*f_in, FILE*f_out){
  fclose(f_in);
  fclose(f_out);
  return EXIT_SUCCESS;
}

int execute_action(FILE* f_in, FILE * f_out, int check, long k)
//iterate over the in_file and execute action for each line,
// then write into out_file
{
  char line[MAX_LINE] = {0};
  while(fgets(line, MAX_LINE, f_in)){
    if (check==ENCODE){
      encode(line, k);
    }
    if(check==DECODE){
      decode(line, k);
    }
    fputs(line, f_out);
  }
  return EXIT_SUCCESS;
}

int run_tests()
//run all tests from tests.c
{
    return(test_encode_non_cyclic_lower_case_positive_k ()||
    test_encode_cyclic_lower_case_negative_k ()||
    test_encode_cyclic_upper_case_positive_k ()||
    test_encode_non_cyclic_lower_case_special_char_negative_k ()||
    test_encode_cyclic_lower_case_special_char_positive_k ()||
    test_decode_cyclic_upper_case_positive_k ()||
    test_decode_cyclic_lower_case_negative_k ()||
    test_decode_cyclic_lower_case_special_char_positive_k ()||
    test_decode_non_cyclic_lower_case_positive_k ()||
    test_decode_non_cyclic_lower_case_special_char_negative_k ());
//    printf("all tested");
}
/*
int close_files(FILE**files){
    for(int i= 0; i< 2; i++)
    {
      fclose(files[i]);
      //files[i] == NULL;
    }
    return EXIT_SUCCESS;
}
*/
/*FILE ** open_in_out_files(char **argv){
  //const char* in = argv[3];
  FILE *f_in = fopen(argv[IN], "r");
  if(f_in == NULL){
    printf("%s\n", argv[IN]);
    fprintf(stderr, "The given file is invalid1\n");
    FILE ** files = {NULL};
    return files;
  }
  //open out file on write with destination path
  const char* out = argv[OUT];
  FILE *f_out = fopen(out, "w");
  if(f_out == NULL)
  {

    fprintf(stderr, "The given file is invalid2\n");
    fclose(f_in);
    FILE ** files = {NULL};
    return files;
  }
  FILE ** files = {f_in, f_out};
  return files;

}
*/
/*
int check_files_open_failure(FILE* files[]){
  for(int i=0; i<2; i++){
    if(files[i]==NULL){
      fprintf(stderr, "The given file is invalid.\n");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
*/
/*
int execute_action_files(FILE** files, int check, long k){
    char line[MAX_LINE] = {0};
    FILE * file_in = files[IN_FILE];
    FILE * file_out = files[OUT_FILE];
    while(fgets(line, MAX_LINE, file_in)){
        if (check==ENCODE){
            encode(line, k);
            printf("%s, %ld", line, k);
        }
        if(check==DECODE){
            decode(line, k);
        }
        fputs(line, file_out);
    }
    return EXIT_SUCCESS;
}
*/
/*
FILE ** files = open_in_out_files (argv);
if(files[IN_FILE] == NULL){
  return EXIT_FAILURE;
}
execute_action_files(files, check, k);
close_files(files);
return EXIT_SUCCESS;
*/