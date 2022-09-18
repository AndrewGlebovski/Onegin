/**
 * \file
 * \brief Contains macros
*/

#include <stdio.h>

#define ASSERT(condition, msg, action) \
do \
    if (!(condition)) { \
        printf("%s | %s in function %s in line %d\n", \
        msg, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
        action; \
    } \
while(0)
