/**
 * \file
 * \brief Contains log and assert macros
*/

#include <stdio.h>


extern FILE *LOG_FILE;


#define ASSERT_AND_LOG(condition, error, msg, action) \
do {\
    if (!LOG_FILE) \
        fprintf(stderr, "No log file"); \
    \
    if (!(condition) && LOG_FILE) { \
        fprintf(LOG_FILE, "%s in function %s in line %d\n[%.3d] %s\n\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, error, msg); \
        fflush(LOG_FILE); \
        action; \
    } \
} while(0)


#define ASSERT(condition, error, msg, action) \
do {\
    if (!(condition)) { \
        fprintf(stdout, "%s in function %s in line %d\n[%.3d] %s\n\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, error, msg); \
        action; \
    } \
} while(0)
