/**
 * \file
 * \brief Main file of this program
*/

#include <stdlib.h>
#include "onegin.hpp"


int main() {
    FILE *input = fopen("debug/input.txt", "r");
    FILE *output = fopen("debug/output.txt", "w");

    StringParser parser;

    read_parser(&parser, NULL);

    sort_lines(parser.lines, parser.size, &qsort, &front_compare);

    print_lines(parser.lines, output);

    free_parser(&parser);

    fclose(input);
    fclose(output);

    return 0;
}
