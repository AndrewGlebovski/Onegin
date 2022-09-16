/**
 * \file
 * \brief Main file of this program
*/

#include <stdlib.h>
#include "onegin.hpp"


int main() {
    FILE *input = fopen("debug/input.txt", "r");
    FILE *output = fopen("debug/output.txt", "w");

    StringPointer *poem;
    long size = read_poem(&poem, input);

    if (size == 0)
        return 1;

    if (sort_poem(poem, size, &qsort, &front_compare))
        return 1;

    print_poem(poem, output);

    fclose(input);
    fclose(output);

    return 0;
}
