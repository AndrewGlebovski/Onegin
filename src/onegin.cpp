/**
 * \file onegin.cpp
 * \brief Contains sorting functions
*/

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "onegin.hpp"


/**
 * \brief Get next alpha symbol in string
 * \param [in] str String to search alpha in
 * \return Pointer to the first element found
*/
const char *get_next_alpha(const char *str);


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
 * \brief Get previous alpha symbol in string
 * \param [in] str String to search alpha in
 * \return Pointer to the first element found
*/
const char *get_prev_alpha(const char *str);


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
 * \brief Swaps two values
 * \param [in] ptrA The first element to swap
 * \param [in] ptrB The second element to swap
 * \param [in] size Element size in bytes
*/ 
void swap(void *ptrA, void *ptrB, size_t size);


/**
 * \brief Sorts an array
 * \param [in] arr Array to sort
 * \param [in] size Array size
 * \param [in] s Element size in bytes
 * \param [in] cmp Compare function
*/ 
void bubble_sort(void *arr, size_t size, size_t s, int (*cmp)(const void *, const void*));


const char *get_next_alpha(const char *str) {
    while (!isalpha(*str++)) {
        if (*str == '\0') 
            return str;
    }
    
    return str - 1;
}


int front_compare(const void *ptrA, const void *ptrB) {
    const char *a = ((StringPointer *) ptrA) -> str;
    const char *b = ((StringPointer *) ptrB) -> str;
    
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


const char *get_prev_alpha(const char *str) {
    while (!isalpha(*str--)) {
        if (*str == '\0') 
            return str;
    }
    
    return str + 1;
}


int back_compare(const void *ptrA, const void *ptrB) {
    const char *a = ((StringPointer *) ptrA) -> str + ((StringPointer *) ptrA) -> len * sizeof(char); 
    const char *b = ((StringPointer *) ptrB) -> str + ((StringPointer *) ptrB) -> len * sizeof(char);
    
    while (1) {
        a = get_prev_alpha(a);
        b = get_prev_alpha(b);

        if (*a == '\0' || *b == '\0')
            break;

        if (*a-- != *b--)
            break;
    }

    return *(a + 1) - *(b + 1);
}


void sort_poem(StringPointer poem[], unsigned int poem_size) {
    bubble_sort(poem, poem_size, sizeof(*poem), &back_compare);
}


void swap(void *ptrA, void *ptrB, size_t size) {
    char *tmp = (char *) calloc(size, sizeof(char));
    memmove(tmp, ptrA, size);
    memmove(ptrA, ptrB, size);
    memmove(ptrB, tmp, size);
    free(tmp);
}


void bubble_sort(void *arr, size_t size, size_t s, int (*cmp)(const void *, const void*)) {
    for(size_t i = 0; i < size - 1; i++) {
        for(size_t j = i + 1; j < size; j++) {
            void *ptrA = (char *) arr + j * s, *ptrB = (char *) arr + i * s;

            if (cmp(ptrA, ptrB) < 0)
                swap(ptrA, ptrB, s);
        }
    }
}
