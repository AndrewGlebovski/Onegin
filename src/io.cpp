/**
 * \file
 * \brief Contains input and output functions
*/

#include <stdlib.h>
#include "onegin.hpp"


int read_parser(StringParser *parser, FILE *stream) {
    ASSERT(parser, "StringParser was NULL", return 1);
    ASSERT(stream, "File was NULL", return 1);

    long lines = 0, chars = 0;
    char line[100];
    while(fgets(line, 1000, stream) != NULL) 
        lines++;

    chars = ftell(stream);

    rewind(stream);

    char *storage = (char *) calloc(chars, sizeof(char));

    parser -> lines = (String *) calloc(lines + 1, sizeof(String));
    parser -> text = storage;
    parser -> status = FILL;

    for(int l = 0; l < lines; l++) {
        (parser -> lines)[l] = {storage, 0};
        int c = 0;

        while((c = fgetc(stream)) != '\n')
            *storage++ = (char) c;

        (parser -> lines)[l].len = (int)(storage - (parser -> lines)[l].str);
        
        *storage++ = '\0';
    }

    (parser -> lines)[lines] = {nullptr, -1};
    parser -> size = lines;

    return 0;
}


int print_lines(String lines[], FILE *stream) {
    ASSERT(lines, "Lines was null", return 1);
    ASSERT(stream, "File was NULL", return 1);

    for(int i = 0; lines[i].str != nullptr && lines[i].len != -1; i++) {
        fprintf(stream, "%s\n", lines[i].str);
        fflush(stream);
    }

    return 0;
}


int free_parser(StringParser *parser) {
    ASSERT(parser, "StringParser was NULL", return 1);
    ASSERT(parser -> status == FILL, "Double free is not allowed", return 1);
    ASSERT(parser -> text != nullptr, "Text was NULL", return 1);
    ASSERT(parser -> lines != nullptr, "Lines was NULL", return 1);

    free(parser -> text);
    free(parser -> lines);

    parser -> status = FREE;
    parser -> size = 0;

    return 0;
}
