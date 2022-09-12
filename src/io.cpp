/**
 * \file io.cpp
 * \brief Contains input and output functions
*/

#include <stdlib.h>
#include "onegin.hpp"


int read_poem(char ***poem, FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    int lines = 0, chars = 0;
    char line[100];
    while(fgets(line, 1000, stream) != NULL) 
        lines++;

    chars = ftell(stream);

    rewind(stream);

    *poem = (char **) calloc(lines, sizeof(char *));

    char *storage = (char *) calloc(chars, sizeof(char));

    for(int l = 0; l < lines; l++) {
        (*poem)[l] = storage;
        int c = 0;

        while((c = fgetc(stream)) != '\n')
            *storage++ = (char) c;

        *storage++ = '\0';
    }

    return lines;
}


void print_poem(char *poem[], FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    for(int i = 0; poem[i] != NULL; i++) {
        fprintf(stream, "%s\n", poem[i]);
        fflush(stream);
    }
}
