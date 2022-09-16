/**
 * \file
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
 * \brief Get previous alpha symbol in string
 * \param [in] str String to search alpha in
 * \return Pointer to the first element found
*/
const char *get_prev_alpha(const char *str);


/**
 * \brief Swaps two values
 * \param [in] ptrA The first element to swap
 * \param [in] ptrB The second element to swap
 * \param [in] size Element size in bytes
*/ 
void swap(void *ptrA, void *ptrB, size_t size);


int sort_poem(
    StringPointer poem[], long size, 
    void (*sort)(void *, size_t, size_t, int (*cmp)(const void *, const void*)), 
    int (*cmp)(const void *, const void *)
) {
    if (!sort) {
        fprintf(stderr, "Sort function was NULL");
        return 1;
    }

    if (!cmp) {
        fprintf(stderr, "Compare function was NULL");
        return 1;
    }

    (*sort)(poem, size, sizeof(*poem), cmp);
    return 0;
}


void bubble_sort(
    void *arr, size_t size, size_t s, 
    int (*cmp)(const void *, const void*)
) {
    for(size_t i = 0; i < size - 1; i++) {
        for(size_t j = i + 1; j < size; j++) {
            void *ptrA = (char *) arr + j * s, *ptrB = (char *) arr + i * s;

            if (cmp(ptrA, ptrB) < 0)
                swap(ptrA, ptrB, s);
        }
    }
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


void swap(void *ptrA, void *ptrB, size_t size) {
    char *tmp = (char *) calloc(size, sizeof(char));
    memmove(tmp, ptrA, size);
    memmove(ptrA, ptrB, size);
    memmove(ptrB, tmp, size);
    free(tmp);
}


const char *get_next_alpha(const char *str) {
    while (!isalpha(*str++)) {
        if (*str == '\0') 
            return str;
    }
    
    return str - 1;
}


const char *get_prev_alpha(const char *str) {
    while (!isalpha(*str--)) {
        if (*str == '\0') 
            return str;
    }
    
    return str + 1;
}
