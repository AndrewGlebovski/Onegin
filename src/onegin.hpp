/**
 * \file
 * \brief It's a header file
*/

#include <stdio.h>


/// This structure contains string and its size
typedef struct {
    const char *str = nullptr; ///< String
    int len = -1; ///< Strings's length
} StringPointer;


/**
 * \brief Sorts the poem
 * \param [out] poem Array of strings to sort
 * \param [in] size Poem's actual size
 * \param [in] sort Sorting function
 * \param [in] cmp Compare function
 * \return Exit code. 0 - OK, 1 - FAIL
 * \warning Function doesn't work correctly with NULL elements
*/
int sort_poem(
    StringPointer poem[], long size, 
    void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void*)), 
    int (*cmp)(const void *, const void *)
);


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


/**
 * \brief Compares two strings using get_next_alpha()
 * \param [in] ptrA The first element to compare
 * \param [in] ptrB The second element to compare
 * \return Standart compare function output
 * 
 * \note This function is used in sort_poem() as compare function. 
 * So it takes pointers to elements of array of strings
*/
int front_compare(const void *ptrA, const void *ptrB);


/**
 * \brief Compares two strings using get_prev_alpha() (comparing starts from end)
 * \param [in] ptrA The first element to compare
 * \param [in] ptrB The second element to compare
 * \return Standart compare function output
 * 
 * This function is used in sort_poem() as compare function. 
 * So it takes pointers to elements of array of strings
*/
int back_compare(const void *ptrA, const void *ptrB);


/**
 * \brief Sorts an array
 * \param [in] arr Array to sort
 * \param [in] size Array size
 * \param [in] s Element size in bytes
 * \param [in] cmp Compare function
*/ 
void bubble_sort(
    void *arr, size_t size, size_t s, 
    int (*cmp)(const void *, const void*)
);
