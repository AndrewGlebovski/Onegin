/**
 * \file
 * \brief Contains sorting and comparing functions
*/

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "onegin.hpp"


/**
 * \brief Universal compare for strings
 * \param [in] ptrA The first element to compare
 * \param [in] sizeA The first element size
 * \param [in] ptrB The second element to compare
 * \param [in] sizeB The second element size
 * \param [in] step Step of iteration
*/ 
int compare(const char *ptrA, int sizeA, const char *ptrB, int sizeB, const int step);


/**
 * \brief Swaps two values
 * \param [in] ptrA The first element to swap
 * \param [in] ptrB The second element to swap
 * \param [in] size Element size in bytes
*/ 
void swap(void *ptrA, void *ptrB, size_t size);


int sort_lines(String lines[], int size, sort_t sort, cmp_t cmp) {
    ASSERT_AND_LOG(sort, INVALID_ARGUMENT, "Sort function was NULL", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(cmp, INVALID_ARGUMENT, "Compare function was NULL", return INVALID_ARGUMENT);

    (*sort)(lines, size, sizeof(*lines), cmp);
    return OK;
}


void bubble_sort(void *arr, size_t size, size_t s, cmp_t cmp) {
    for(size_t i = 0; i < size - 1; i++) {
        for(size_t j = i + 1; j < size; j++) {
            void *ptrA = (char *) arr + j * s, *ptrB = (char *) arr + i * s;

            if (cmp(ptrA, ptrB) < 0)
                swap(ptrA, ptrB, s);
        }
    }
}


int compare(const char *ptrA, int sizeA, const char *ptrB, int sizeB, const int step) {
    ASSERT(ptrA, OK, "ptrA was NULL", return 1);
    ASSERT(ptrB, OK, "ptrB was NULL", return -1);

    do {
        while (!isalnum(*ptrA) && sizeA--) ptrA += step;
        while (!isalnum(*ptrB) && sizeB--) ptrB += step;

    } while (*(ptrA += step) == *(ptrB += step) && sizeA-- && sizeB--);

    return *(ptrA - step) - *(ptrB - step);
}


int front_compare(const void *ptrA, const void *ptrB) {
    ASSERT(ptrA, OK, "ptrA was NULL", return 1);
    ASSERT(ptrB, OK, "ptrB was NULL", return -1);

    return compare(
        ((strptr_t) ptrA) -> str, ((strptr_t) ptrA) -> len * sizeof(char),
        ((strptr_t) ptrB) -> str, ((strptr_t) ptrB) -> len * sizeof(char),
        1
    );
}


int back_compare(const void *ptrA, const void *ptrB) {
    ASSERT(ptrA, OK, "ptrA was NULL", return 1);
    ASSERT(ptrB, OK, "ptrB was NULL", return -1);

    return compare(
        ((strptr_t) ptrA) -> str + ((strptr_t) ptrA) -> len * sizeof(char), ((strptr_t) ptrA) -> len * sizeof(char),
        ((strptr_t) ptrB) -> str + ((strptr_t) ptrB) -> len * sizeof(char), ((strptr_t) ptrB) -> len * sizeof(char),
        -1
    );
}


void swap(void *ptrA, void *ptrB, size_t size) {
    ASSERT_AND_LOG(ptrA, INVALID_ARGUMENT, "ptrA was NULL", return);
    ASSERT_AND_LOG(ptrB, INVALID_ARGUMENT, "ptrB was NULL", return);
    ASSERT_AND_LOG(size > 0, INVALID_ARGUMENT, "size was not correct", return);

    char *tmp = (char *) calloc(size, sizeof(char));
    memmove(tmp, ptrA, size);
    memmove(ptrA, ptrB, size);
    memmove(ptrB, tmp, size);
    free(tmp);
}
