/**
 * \file
 * \brief Contains input and output functions
*/

#include <stdlib.h>
#include "onegin.hpp"


int read_poem(StringParser *poem, FILE *stream) {
    if (!stream) {
        fprintf(stderr, "File pointer was null");
        return 1;
    }

    long lines = 0, chars = 0;
    char line[100];
    while(fgets(line, 1000, stream) != NULL) 
        lines++;

    chars = ftell(stream);

    rewind(stream);

    char *storage = (char *) calloc(chars, sizeof(char));

    poem -> lines = (String *) calloc(lines + 1, sizeof(String));
    poem -> text = storage;
    poem -> status = FILL;

    for(int l = 0; l < lines; l++) {
        (poem -> lines)[l] = {storage, 0};
        int c = 0;

        while((c = fgetc(stream)) != '\n')
            *storage++ = (char) c;

        (poem -> lines)[l].len = (int)(storage - (poem -> lines)[l].str);
        
        *storage++ = '\0';
    }

    (poem -> lines)[lines] = {nullptr, -1};
    poem -> size = lines;

    return 0;
}


void print_lines(String lines[], FILE *stream) {
    if (!lines) {
        fprintf(stderr, "Lines was null");
        return;
    }

    if (!stream) {
        fprintf(stderr, "File pointer was null");
        return;
    }

    for(int i = 0; lines[i].str != nullptr && lines[i].len != -1; i++) {
        fprintf(stream, "%s\n", lines[i].str);
        fflush(stream);
    }
}


void free_poem(StringParser *poem) {
    if (!poem) {
        fprintf(stderr, "Poem pointer was null");
        return;
    }

    if (poem -> status == FILL) {
        free(poem -> text);
        free(poem -> lines);
        poem -> status = FREE;
        poem -> size = 0;
    }
    else {
        printf("Double free is not allowed");
        return;
    }
}
