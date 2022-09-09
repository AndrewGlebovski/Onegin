#include "onegin.hpp"


int main() {
    FILE *input = fopen("debug/input.txt", "r");
    FILE *output = fopen("debug/output.txt", "w");

    char *poem[MAX_LINES];
    unsigned int size = read_poem(poem, input);

    sort_poem(poem, size);

    print_poem(poem, output);

    return 0;
}
