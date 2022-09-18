/**
 * \file
 * \brief Contains log and assert macros
*/

#include <stdio.h>


/// Contains exit codes (error codes) for functions
typedef enum {
    OK               = 0, ///< Well done!
    INVALID_ARGUMENT = 1, ///< Invalid argument passed to function
    FILE_NOT_FOUND   = 2, ///< Couldn't open this file
    ALLOCATE_FAIL    = 3, ///< Allocate memory function returns NULL
    INVALID_COMMAND  = 4  ///< Invalid command argument passed to run.exe
} EXIT_CODE;


/// All log messages will be printed to this file
extern FILE *LOG_FILE;


/**
 * \brief This assert throw errors to log file
 * \param [in] condition Condition to check
 * \param [in] error This error code will be printed if condition fails
 * \param [in] msg This message will be printed if condition fails
 * \param [in] action This code will be executed if condition fails
*/
#define ASSERT_AND_LOG(condition, error, msg, action) \
do {\
    if (!LOG_FILE) \
        fprintf(stderr, "No log file"); \
    \
    else if (!(condition)) { \
        fprintf(LOG_FILE, "%s in function %s in line %d\n[%.3d] %s\n\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, error, msg); \
        fflush(LOG_FILE); \
        action; \
    } \
} while(0)


/**
 * \brief This assert throw errors to stderr
 * \param [in] condition Condition to check
 * \param [in] error This error code will be printed if condition fails
 * \param [in] msg This message will be printed if condition fails
 * \param [in] action This code will be executed if condition fails
*/
#define ASSERT(condition, error, msg, action) \
do {\
    if (!(condition)) { \
        fprintf(stderr, "%s in function %s in line %d\n[%.3d] %s\n\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, error, msg); \
        action; \
    } \
} while(0)
