/**
 * \file
 * \brief It's a header file
*/

#include <stdio.h>


/// This structure contains string and its size
typedef struct {
    const char *str = nullptr; ///< String
    int len = -1; ///< Strings's length
} String;


typedef void (*sort_t)(void *arr, size_t size, size_t elem_size, int (*cmp)(const void *ptrA, const void*ptrB));


typedef int (*cmp_t)(const void *ptrA, const void *ptrB);


typedef enum {
    INIT = 0,
    FILL = 1,
    FREE = 2
} POEM_STATUS;


typedef struct {
    POEM_STATUS status = INIT;
    String *lines = nullptr;
    char* text = nullptr;
    long size = -1;
} StringParser;



/**
 * \brief Sorts the poem
 * \param [out] poem Array of strings to sort
 * \param [in] size StringParser's actual size
 * \param [in] sort Sorting function
 * \param [in] cmp Compare function
 * \return Exit code. 0 - OK, 1 - FAIL
 * \warning Function doesn't work correctly with NULL elements
*/
int sort_poem(StringParser *poem, sort_t sort, cmp_t cmp);


/**
 * \brief Reads poem from the given file
 * \param [out] poem Pointer to an array of strings
 * \param [in] stream File for input
 * \return Number of lines read
 * \note New line symbol will be discarded
*/
int read_poem(StringParser *poem, FILE *stream);


/**
 * \brief Prints array of #String to the given file
 * \param [in] lines Array of #String
 * \param [in] stream File for output
 * \note New line symbol will be added to the end of each line
*/
void print_lines(String lines[], FILE *stream) ;


void free_poem(StringParser *poem);


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
void bubble_sort(void *arr, size_t size, size_t s, cmp_t cmp);
