/**
 * \file onegin.hpp
 * \brief It's a header file
*/

#include <stdio.h>


/// Length of the poem's line
const int MAX_LENGTH = 100;


/**
 * \brief Sorts the poem using qsort()
 * \param [out] poem Array of strings to sort
 * \param [in] poem_size Poem's actual size
 * \warning Function will not work if you pass an incorrect size.
 * You should pass only number of not NULL elements
*/
void sort_poem(char *poem[], unsigned int poem_size);


/**
 * \brief Reads poem from the given file
 * \param [out] poem Pointer to an array of strings
 * \param [in] stream File for input
 * \return Number of lines read
*/
int read_poem(char ***poem, FILE *stream);


/**
 * \brief Prints poem to the given file
 * \param [in] poem Array of strings
 * \param [in] stream File for output
*/
void print_poem(char **poem, FILE *stream);
