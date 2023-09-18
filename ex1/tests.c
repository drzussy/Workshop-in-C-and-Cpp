#include "tests.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define K_1 3
#define K_2 -1
#define K_3 -23
#define K_5 270
#define ENCODE 100
#define DECODE 101
#define TEST 102

//#define TEST_1_FAIL "test_encode_non_cyclic_lower_case_positive_k failed"
//int (char in[], const char out[]);
//int decode_test_template(char in[], const char out[]);
//int run_test();
//int test_cyclic_all_case_large_k();
/*
long convert_k_to_long(char* s);
long test_convert_k_to_long();
int k_format_check(char* k, int len_k);
int test_format_check_mixed();
int test_format_check_all_numerical();
int test_format_check_non_numerical();
int check_input_size(int argc, char* args[]);
int test_check_input_size_size_4_ENCODE();
int test_check_input_size_size_4_DECODE();
int test_check_input_size_size_4_test();
int test_check_input_size_size_1_test();
int test_check_input_size_size_4_random();
int check_action(int argc, char* args[]);*/


//void tester();

/*nt run_tests(){
  assert(test_encode_non_cyclic_lower_case_positive_k()==0);
  assert(test_encode_cyclic_lower_case_negative_k()==0);
  assert(test_encode_cyclic_upper_case_positive_k()==0);
  assert(test_encode_non_cyclic_lower_case_special_char_negative_k()==0);
  assert(test_encode_cyclic_lower_case_special_char_positive_k()==0);
  assert(test_decode_cyclic_upper_case_positive_k()==0);
  assert(test_decode_cyclic_lower_case_negative_k()==0);
  assert(test_decode_cyclic_lower_case_special_char_positive_k()==0);
  assert(test_decode_non_cyclic_lower_case_positive_k()==0);
  assert(test_decode_non_cyclic_lower_case_special_char_negative_k()==0);
  assert(test_cyclic_all_case_large_k());

  assert(test_convert_k_to_long());
  assert(test_format_check_mixed());
  assert(test_format_check_all_numerical());
  assert(test_format_check_non_numerical());
  assert(ENCODE == test_check_input_size_size_4_ENCODE());
  assert(DECODE ==test_check_input_size_size_4_DECODE());
  assert(EXIT_FAILURE == test_check_input_size_size_4_test());
  assert(TEST==test_check_input_size_size_1_test());
  assert(EXIT_FAILURE == test_check_input_size_size_4_random());
  return EXIT_SUCCESS;
}*/
/*
int (char in[], const char out[]){
  for(unsigned int i=0;i<strlen(in); i++)
  {
    if(out[i] != in[i]){
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int decode_test_template(char* in, const char* out)
{
  for(unsigned int i=0;i<strlen(in); i++)
  {
    if(out[i] != in[i]){
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;

}*/
char s1[] = {"abc"};
char t[] = {"def"};
// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  encode (s1, K_1);
  return strcmp(s1, t);
}

// See full documentation in header file
char s10[] = {"ab!"};
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
  encode (s10, K_2);
  return strcmp(s10, "za!");
}

char s2[] = {"z1!"};

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
  encode (s2, K_2);
  return  strcmp(s2, "y1!");
}
char s3[] = {"abc!"};
// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
  // your code goes here
  encode (s3, K_2);
  return strcmp(s3, "zab!");
}
char s4[] = {"ABC"};
// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
  encode (s4, K_1);
  return  strcmp(s4,"DEF");
}

char s9[] = {"X!Y"};
// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
  decode (s9, K_1);
  return strcmp(s9, "U!V");
}

char s5[] = {"def"};
// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  decode (s5, K_1);
  return strcmp (s5, "abc");
}

char s6[] = {"xyz"};
// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  decode (s6, K_1);
  return strcmp (s6, "uvw");
}
char s7[] = {"de!"};
// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
  decode (s7, K_1);
  return strcmp (s7, "ab!");
}
char s8[] = {"x!@"};
// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
  decode (s8, K_3);
  return strcmp (s8, "u!@");
}

int test_cyclic_all_case_large_k()
{  
  decode (s10, K_5);
  return strcmp(s10, "Ji!");
}
/*
long convert_k_to_long(char* s)
{
  int len_k = strlen(s);
  //convert k to int
  //printf("%s\n", s);
  //printf("%d\n", strlen(s));
  long num_k = strtol (s, NULL, len_k+1);
  return num_k;
}
char* st = {"123456789"};
long test_convert_k_to_long(){
  return (123456789 == convert_k_to_long(st));
}

int k_format_check(char* k, int len_k){
  //checks that k is all numerical
  for(int i=0;i<len_k;i++){
    if(k[i]< 48|| 57<k[i]){
      //if not return 1
      return EXIT_FAILURE;
    }
  }
  //if yes return 0
  return EXIT_SUCCESS;
}

int test_format_check_all_numerical(){
  char s[] = {"123456789"};
  //printf("%ld", k_format_check(s, strlen(s)));
  return (EXIT_SUCCESS == k_format_check(s, strlen(s)));
}

int test_format_check_non_numerical(){
  char*s = {"asdfghjkl"};
  return (EXIT_FAILURE==k_format_check(s, strlen(s)));
}

int test_format_check_mixed(){
  char*s = {"a1s2d3d4f"};
  return (EXIT_FAILURE == k_format_check(s, strlen(s)));
}

int check_input_size(int argc, char* args[])
//checks input size and returns action type
{
  if(argc!=4 && argc!=1){
    fprintf(stderr, "The program receives 1 or 4 arguments only.\n");
    return EXIT_FAILURE;
  }
  return check_action(argc, args);
}

int check_action(int argc, char* args[])
{
  if (argc == 4)
  {
    if (!strcmp (args[0], "encode"))
    {
      return ENCODE;
    }
    else if (!strcmp (args[0], "decode"))
    {
      return DECODE;
    }
  }
  else if (!strcmp (args[0], "test"))
  {
    return TEST;
  }
  return EXIT_FAILURE;
}

int test_check_input_size_size_4_ENCODE(){
  char a[] = {"0"};
  char b[] = {"encode"};
  char*s= {a, b};
  return check_input_size(4, &s);
}

int test_check_input_size_size_4_DECODE(){
  char *s = {"decode"};
  return check_input_size(4, &s);
}

int test_check_input_size_size_4_test(){
  char*s = {"test"};
  return check_input_size(4, &s);
}

int test_check_input_size_size_1_test(){
  char*s = {"test"};
  return check_input_size(1, &s);
}

int test_check_input_size_size_4_random(){
  char*s = {"random"};
  return check_input_size(4, &s);
}
*/

/*
void tester(){
  long a[] = {10, 0, 20, 0};
  long* p = a;
  while(*p++);
  printf("%td", --p - a);
}*/