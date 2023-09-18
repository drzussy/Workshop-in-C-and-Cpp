#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21
/**
 * Define struct BusLine.
 * @param name - char[]
 * @param distance - int
 * @param duration - int
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

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
 * @param i - right side of smaller.
 * @param j - current element being compared to pivot.
* Divide array into four sections.
* smaller then pivot, bigger, unknown, pivot.
 * if busline[i] < pivot: add 1 to i and swap the element to the right side
 * of smallers.
 * if not keep iterating
 * at end of pass, swap pivot with left most element in bigger.
*/
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
