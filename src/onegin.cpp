/**
 * \file onegin.cpp
 * \brief Contains sorting functions
*/

#include <stdlib.h>
#include <ctype.h>
#include "onegin.hpp"


/**
 * \brief Get next alpha symbol in string
 * \param [in] str String to search alpha in
 * \return Pointer to first alpha element
*/
const char *get_next_alpha(const char *str);


/**
 * \brief Compares two strings using get_next_alpha()
 * \param [in] ptrA The first element to compare
 * \param [in] ptrB The second element to compare
 * \return Standart compare function output
 * 
 * This function is used in sort_poem() as compare function. 
 * So it takes pointers to elements of array of strings
*/
int front_compare(const void *ptrA, const void *ptrB);


const char *get_next_alpha(const char *str) {
    while (!isalpha(*str++)) {
        if (*str == '\0') 
            return str;
    }
    
    return str - 1;
}


int front_compare(const void *ptrA, const void *ptrB) {
    const char *a = *(const char **) ptrA, *b = *(const char **) ptrB;
    
    while (1) {
        a = get_next_alpha(a);
        b = get_next_alpha(b);

        if (*a == '\0' || *b == '\0')
            break;

        if (*a++ != *b++)
            break;
    }

    return *(a - 1) - *(b - 1);
}


void sort_poem(char *poem[], unsigned int poem_size) {
    qsort(poem, poem_size, sizeof(*poem), &front_compare);
}
