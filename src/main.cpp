/**
 * \file
 * \brief Main file of this program
*/

#include <stdlib.h>
#include "onegin.hpp"
#include "parser.hpp"


int main(int argc, char *argv[]) {
    FILE *input = nullptr;
    FILE *output = fopen("debug/output.txt", "w");
    int cmp_mode = 0;

    command_list[0].data = &input;
    command_list[1].data = &output;
    command_list[2].data = &cmp_mode;
    parse(argc, argv);

    StringParser parser;

    read_parser(&parser, input);

    if (cmp_mode)
        sort_lines(parser.lines, parser.size, &qsort, &back_compare);
    else
        sort_lines(parser.lines, parser.size, &qsort, &front_compare);

    print_lines(parser.lines, output);

    free_parser(&parser);

    fclose(input);
    fclose(output);

    return 0;
}
