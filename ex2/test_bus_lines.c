#include "test_bus_lines.h"
#include <stdbool.h>
#include <string.h>


int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  //use pointer arithmetic
  BusLine * prev_p = start;
  for(BusLine * p = start; p < end; p += 1)
  {
    if(p == start)
    {
      continue;
    }
    if(p->distance < prev_p->distance)
    {
      return false;
    }
    prev_p++;
    //prev_p += sizeof(BusLine);
  }
  //return success
  return true;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  //use pointer arithmetic
//  for(int i=0; i < end-1)
  BusLine * prev_p = start;
  for(BusLine * p = start; p < end-1; p ++)
  {
    if(p == start)
    {
      continue;
    }
    //printf("comparing %d < %d\n", p->duration , prev_p->duration);
    if(p->duration < prev_p->duration)
    {
      return false;
    }
    prev_p ++;
  }
  //return success
  return true;
}

int is_sorted_by_name (BusLine *start, BusLine *end)
{
  //use pointer arithmetic
  {
    //use pointer arithmetic
    BusLine * prev_p = start;
    for(BusLine * p = start; p < end-1; p +=1)
    {
      if(p == start)
      {
        continue;
      }
      //use strcmp to ascertain order of names
      if(strcmp(prev_p->name, p->name) > 0)
      {
        return false;
      }
      prev_p ++;
    }
  }
  //return success
  return true;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  //calc sizes of both arrays
  int origin_size = end_sorted - start_sorted;
  int sorted_size = end_original - start_original;
  if(origin_size != sorted_size)
  {
    return false;
  }
// iterate over original array in outer loop
  for(int j=0; j < origin_size; j++)
  {
    bool found = false;
    // compare the current BusLine in origin array to every BusLine in sorted
    // array to see if it exists. if found then change found to true
    for (int i = 0; i < origin_size; i++)
    {
      if(!strcmp((start_original+j)->name, (start_sorted+i)->name))
      {
        found = true;
      }
    }
    //if not a BusLine is not found then return false
    if(found == false){
      return false;
    }
  }
  //all BusLines exist in sorted, return true
  return true;
}

