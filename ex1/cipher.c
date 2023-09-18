#include "cipher.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#define RANGE 26
#define UPPER 65
#define LOWER 97


/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.


// See full documentation in header file
//assume all input is valid, test for that in main
void encode (char s[], int k)
{
  //range is of alphabet, modulate by range, add range to confirm k is positive
  k = (k % RANGE + RANGE) % RANGE;
  //iterate over string and encode each letter by k
  for (unsigned int i = 0; i < strlen (s); ++i)
  {
    if (isupper(s[i]))
    {
      /*modulate by uppercase, add k, modulate again to keep in range, add
      back uppercase*/
      s[i] = (s[i] % UPPER + k) % RANGE + UPPER;
    }
    else if (islower(s[i]))
    {
      /*modulate by lowercase (90), add k, modulate again to keep in range,
      back lowercase*/
      s[i] = (s[i] % LOWER + k) % RANGE + LOWER;
    }
  }
}


// See full documentation in header file
void decode (char s[], int k)
{
  encode(s, (-k));
}

/*
// your code goes here
k = (k%RANGE+RANGE)%RANGE;
//iterate over string and encode each letter by k
for(int i=0; i<strlen(s);++i){
  if( isupper(s[i])){
    //upper case
    //modulate by uppercase, add k, modulate again to keep in range, add
    //back uppercase
    s[i] = ((s[i]%UPPER)-k)%RANGE+UPPER;
  }
  else if(islower(s[i])){
    //modulate by lowercase (90), add k, modulate again to keep in range,
    //back lowercase
    s[i] = ((s[i]%LOWER)-k)%RANGE+LOWER;;
  }
  else{
    //if not alphabetical ignore
  }
}
*/

