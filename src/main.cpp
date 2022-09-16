/**
 * \file
 * \brief Main file of this program
*/

#include "onegin.hpp"


int main() {
    FILE *input = fopen("debug/input.txt", "r");
    FILE *output = fopen("debug/output.txt", "w");

    StringPointer *poem;
    long size = read_poem(&poem, input);

    if (size == 0)
        return 1;

    sort_poem(poem, size, BUBBLE_SORT, FRONT_CMP);

    print_poem(poem, output);

    fclose(input);
    fclose(output);

    return 0;
}
