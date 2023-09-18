#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * checks that for a given array of BusLines all elements are ordered in
 * ascending order by distance.
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * Checks that for a given array of BusLines all elements are ordered in
 * ascending order by duration.
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
 * Checks that for a given array of BusLines all elements are ordered
 * alphabetically and numericaly in ascending order by name.
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * Uses pointer arithmetic. for each element in one array go over all
 * elements in second array and compare names. If found move to next element
 * in first array and if not return false. If all names found, return true.
 * This function assumes no names are identical.
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
