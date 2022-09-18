/**
 * \file
 * \brief It's a command line arguments parser header
*/

#include <string.h>
#include "macros.hpp"


/**
 * \brief Parses arguments
 * \param [in] argc Number of arguments
 * \param [in] argv Array of arguments
*/
int parse(int argc, char* argv[]);


/// Contains information about command
typedef struct {
	const char* short_name; ///< Command short name
	const char* long_name; ///< Command long name
	int mode; ///< Mode
	void (*func)(char *argv[], void *data); ///< Command parser function
	void *data; ///< Additional data
	const char *desc; ///< Command description
} Command;


/// List describing all commands
extern Command command_list[];
