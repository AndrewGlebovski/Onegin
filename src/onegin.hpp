/**
 * \file
 * \brief It's a header file
*/

#include "logs.hpp"


/// This structure contains string and its size
typedef struct {
    const char *str = nullptr; ///< Pointer
    int len = -1; ///< Length
} String;


/// Sort function template
typedef void (*sort_t)(void *arr, size_t size, size_t elem_size, int (*cmp)(const void *ptrA, const void*ptrB));


/// Compare function template
typedef int (*cmp_t)(const void *ptrA, const void *ptrB);


/// String struct const pointer
typedef const String * strptr_t;


/// #StringViewer possible status
typedef enum {
    INIT = 0, ///< Just initialized
    FILL = 1, ///< Filled with content
    FREE = 2  ///< His memory is free
} POEM_STATUS;


/// Contains array of #String and its size
typedef struct {
    POEM_STATUS status = INIT; ///< Status shows last action with poem (see #POEM_STATUS)
    String *lines = nullptr; ///< Array of strings
    char* text = nullptr; ///< Pointer to an array of chars
    long size = -1; ///< Lines's size
} StringViewer;


/**
 * \brief Sorts the parser
 * \param [out] lines Array of #String to sort
 * \param [in] size array size
 * \param [in] sort Sorting function
 * \param [in] cmp Compare function
 * \return Exit code. 0 - OK, 1 - FAIL
 * \warning Function doesn't work correctly with NULL elements
*/
int sort_lines(String lines[], int size, sort_t sort, cmp_t cmp);


/**
 * \brief Parse each line from file to the array
 * \param [out] parser Pointer to an array of strings
 * \param [in] stream File for input
 * \return Exit code. 0 - OK, 1 - FAIL
 * \note New line symbol will be discarded
*/
int read_parser(StringViewer *parser, FILE *stream);


/**
 * \brief Prints array of #String to the given file
 * \param [in] lines Array of #String
 * \param [in] stream File for output
 * \return Exit code. 0 - OK, 1 - FAIL
 * \note New line symbol will be added to the end of each line
*/
int print_lines(String lines[], FILE *stream) ;


/**
 * \brief Free parser
 * \param [in] parser This parser will be free
 * \return Exit code. 0 - OK, 1 - FAIL
 * \warning If some pointer is null, nothing will be free
*/
int free_parser(StringViewer *parser);


/**
 * \brief Compares two strings from front
 * \param [in] ptrA The first element to compare
 * \param [in] ptrB The second element to compare
 * \return Standart compare function output
 * 
 * \note This function is used in sort_parser() as compare function. 
 * So it takes pointers to elements of array of strings
*/
int front_compare(const void *ptrA, const void *ptrB);


/**
 * \brief Compares two strings from back
 * \param [in] ptrA The first element to compare
 * \param [in] ptrB The second element to compare
 * \return Standart compare function output
 * 
 * \note This function is used in sort_parser() as compare function. 
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
