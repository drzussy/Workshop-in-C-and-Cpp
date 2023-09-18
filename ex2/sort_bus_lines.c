#include "sort_bus_lines.h"
#include <string.h>

//TODO add implementation here
void swap(BusLine* p1, BusLine* p2)
/**
 * swap order of BusLine using pointers.
 * @param p1 pointer to BusLine
 * @param p2 pointer to BusLine
 */
{
  BusLine temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}
void swap_by_sort_type(BusLine* start, BusLine* pivot, SortType sort_type,
                      int *i,
                  const int* j)
/**
 * swap elements in partition by selected SortType using swap() function.
 * @param start
 * @param pivot
 * @param sort_type
 */
{
  if(sort_type == DISTANCE)
  {
    if ((start + *j)->distance <= pivot->distance)
    {
      *i += 1;
      swap ((start + *i), (start + *j));
    }
  }
  if(sort_type == DURATION)
  {
    if ((start + *j)->duration <= pivot->duration)
    {
      *i += 1;
      swap ((start + *i), (start + *j));
    }
  }
}

void bubble_sort (BusLine *start, BusLine *end)
{

  //sort array of BusLines
  BusLine *iterate = start;
  int i, j;
  for(i=0; i<(end-start)-1; i++)
  {
    //not comparing all the last i names that are already sorted
    for(j=0;j<(end-start)-i-1; j++)
    {
      if (0 < strcmp((iterate+j)->name, (iterate+j+1)->name))
      {
        swap (iterate+j, iterate+j+1);
      }
    }
  }
}

void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
  //base case where size equals 1
  if(end-start < 1)
  {
    return;
  }
  //partition
  BusLine *part = partition(start, end, sort_type);
  //quick sort left
  quick_sort(start, part, sort_type);
  //quick sort right
  quick_sort(part+1, end, sort_type);
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  //pivot element is right most (last)
  BusLine * pivot = end - 1;
  //Index i is the end of smaller elements section
  int i = -1;
  //iterate over all the array
  for(int j=0; j<(end-start-1); j++)
  {
    //if the current element is smaller than the pivot element, swap with
    // the next element after i, by selected sort_type.
    swap_by_sort_type(start, pivot, sort_type, &i, &j);

  }
  //after full iteration, the array is divided into elements smaller than
  // pivot and elements bigger. swap pivot with the first element in larger
  // elements section.
  swap((start+i+1), pivot);
  return start+i+1;
}

/**
 * Implement bubble sort on the lines by name.
 * @param i - number of elements bubbled up and ordered
 * @param j - index in current iteration.
 * sort using strcmp to compare alphabetical order.
 */
  void bubble_sort (BusLine *start, BusLine *end);

/**
 * Recursively quick sort an array of BusLines structs by sort_type
 * (duration or distance).
 * Partition and then call quick sort on left and right sides.
 */
  void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * Partition array. Partition is right most element of array.
 *
 */
  BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);

