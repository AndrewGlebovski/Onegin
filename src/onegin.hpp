/**
 * \file
 * \brief It's a header file
*/

#include <stdio.h>


typedef struct {
    const char *str = nullptr;
    int len = -1;
} StringPointer;


typedef enum {
    BUBBLE_SORT = 1,
    QUICK_SORT  = 2
} SORT_FUNC;


typedef enum {
    FRONT_CMP = 1,
    BACK_CMP  = 2
} SORT_MODE;


/**
 * \brief Sorts the poem
 * \param [out] poem Array of strings to sort
 * \param [in] size Poem's actual size
 * \warning Function doesn't work correctly with NULL elements
*/
void sort_poem(StringPointer poem[], long size, SORT_FUNC sort_func, SORT_MODE sort_mode);


/**
 * \brief Reads poem from the given file
 * \param [out] poem Pointer to an array of strings
 * \param [in] stream File for input
 * \return Number of lines read
 * \note New line symbol will be discarded
*/
long read_poem(StringPointer **poem, FILE *stream);


/**
 * \brief Prints poem to the given file
 * \param [in] poem Array of strings
 * \param [in] stream File for output
 * \note New line symbol will be added to the end of each line
*/
void print_poem(StringPointer poem[], FILE *stream);
