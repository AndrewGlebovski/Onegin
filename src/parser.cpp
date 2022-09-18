/**
 * \file
 * \brief Contains command line arguments parser
*/

#include <string.h>
#include "macros.hpp"
#include "parser.hpp"
#include "error.hpp"


void set_input_stream(char *argv[], void *data); ///< -i parser
void set_output_stream(char *argv[], void *data); ///< -o parser
void set_compare_direction(char *argv[], void *data); ///< -cd parser
void show_help(char *argv[], void *data); ///< -h parser


Command command_list[] = {
	{
		"-i", "--input", 
		0, 
		&set_input_stream, 
		nullptr,
		"<relative path to a file> Changes input file"
	},
	{
		"-o", "--output", 
		0, 
		&set_output_stream, 
		nullptr,
		"<relative path to a file> Changes output file"
	},
	{
		"-cd", "--compare-direction", 
		0, 
		&set_compare_direction, 
		nullptr,
		"<integer> Changes compare direction. 0 - front compare, 1 - back compare"
	},
	{
		"-h", "--help", 
		0, 
		&show_help, 
		nullptr,
		"Prints all commands descriptions"
	},
};


int parse(int argc, char* argv[]) {
	ASSERT(argc, "argc was 0", return INVALID_ARGUMENT);
	ASSERT(argv, "argv was NULL", return INVALID_ARGUMENT);

	for(int j = 0; j < argc; j++) {
		int n = sizeof(command_list) / sizeof(Command);
		for(int i = 0; i < n; i++) {
			if (strcmp(command_list[i].short_name, argv[j]) == 0 || strcmp(command_list[i].long_name, argv[j]) == 0)
				(*(command_list[i].func))(&argv[j], command_list[i].data);
		}
	}

	return OK;
}



void set_input_stream(char *argv[], void *data) {
	ASSERT(argv, "argv was NULL", return);
	ASSERT(data, "data was NULL", return);

	if (*(++argv)) {
		ASSERT(fopen(*argv, "r"), "Can't open file, argument ignored", return);

		*((FILE **) data) = fopen(*argv, "r");
	}
	else {
		ASSERT(0, "No filename after argument, argument ignored", return);
	}
}


void set_output_stream(char *argv[], void *data) {
	ASSERT(argv, "argv was NULL", return);
	ASSERT(data, "data was NULL", return);

	if (*(++argv)) {
		ASSERT(fopen(*argv, "w"), "Can't open file, argument ignored", return);

		*((FILE **) data) = fopen(*argv, "w");
	}
	else {
		ASSERT(0, "No filename after argument, argument ignored", return);
	}
}


void set_compare_direction(char *argv[], void *data) {
	ASSERT(argv, "argv was NULL", return);
	ASSERT(data, "data was NULL", return);

	if (*(++argv)) {
		ASSERT(!strcmp(*argv, "0") || !strcmp(*argv, "1"), "Invalid mode, argument ignored", return);

		*((int *) data) = **(argv) - (int) '0';
	}
	else {
		ASSERT(0, "No mode after argument, argument ignored", return);
	}
}


void show_help(char *argv[], void *data) {
	for(size_t i = 0; i < sizeof(command_list) / sizeof(Command); i++) {
		printf("%s %s %s\n", command_list[i].short_name, command_list[i].long_name, command_list[i].desc);
	}
}
