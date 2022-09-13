/**
 * \file main.cpp
 * \brief Main file of this program
*/

#include "onegin.hpp"


int main() {
    FILE *input = fopen("debug/input.txt", "r");
    FILE *output = fopen("debug/output.txt", "w");

    StringPointer *poem;
    unsigned int size = read_poem(&poem, input);

    sort_poem(poem, size);

    print_poem(poem, output);

    fclose(input);
    fclose(output);

    return 0;
}
