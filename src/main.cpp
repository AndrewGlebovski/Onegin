/**
 * \file
 * \brief Main file of this program
*/

#include <stdlib.h>
#include "onegin.hpp"
#include "parser.hpp"



int main(int argc, char *argv[]) {
    FILE *input = fopen("debug/input.txt", "r");
    FILE *output = fopen("debug/output.txt", "w");
    
    enum CMP_DIR{
        FORWARD  = 0,
        BACKWARD = 1
    };
    
    int cmp_dir = FORWARD;

    command_list[0].data = &input;
    command_list[1].data = &output;
    command_list[2].data = &cmp_dir;
    parse_args(argc, argv);

    StringViewer viewer = {};

    read_viewer(&viewer, input);

    if (cmp_dir == BACKWARD)
        sort_lines(viewer.lines, viewer.size, &qsort, &back_compare);
    else
        sort_lines(viewer.lines, viewer.size, &qsort, &front_compare);

    print_lines(viewer.lines, output);

    free_viewer(&viewer);

    fclose(input);
    fclose(output);
    fclose(LOG_FILE);

    return 0;
}
