/**
 * \file
 * \brief Main file of this program
*/

#include <stdlib.h>
#include "onegin.hpp"


int main() {
    FILE *input = fopen("debug/input.txt", "r");
    FILE *output = fopen("debug/output.txt", "w");

    StringParser poem;

    read_poem(&poem, input);

    if (sort_poem(&poem, &qsort, &front_compare))
        return 1;

    print_lines(poem.lines, output);

    free_poem(&poem);
    free_poem(&poem);

    fclose(input);
    fclose(output);

    return 0;
}
