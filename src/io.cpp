/**
 * \file
 * \brief Contains input and output functions
*/

#include <stdlib.h>
#include "macros.hpp"
#include "onegin.hpp"
#include "error.hpp"


int read_parser(StringParser *parser, FILE *stream) {
    ASSERT(parser, "StringParser was NULL", return INVALID_ARGUMENT);
    ASSERT(stream, "File was NULL", return INVALID_ARGUMENT);

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

    ASSERT(parser -> lines, "Not enough memory for lines", return ALLOCATE_FAIL);
    ASSERT(parser -> text, "Not enough memory for text", return ALLOCATE_FAIL);

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

    return OK;
}


int print_lines(String lines[], FILE *stream) {
    ASSERT(lines, "Lines was null", return INVALID_ARGUMENT);
    ASSERT(stream, "File was NULL", return INVALID_ARGUMENT);

    for(int i = 0; lines[i].str != nullptr && lines[i].len != -1; i++) {
        fprintf(stream, "%s\n", lines[i].str);
        fflush(stream);
    }

    return OK;
}


int free_parser(StringParser *parser) {
    ASSERT(parser, "StringParser was NULL", return INVALID_ARGUMENT);
    ASSERT(parser -> status == FILL, "Double free is not allowed", return INVALID_ARGUMENT);
    ASSERT(parser -> text != nullptr, "Text was NULL", return INVALID_ARGUMENT);
    ASSERT(parser -> lines != nullptr, "Lines was NULL", return INVALID_ARGUMENT);

    free(parser -> text);
    free(parser -> lines);

    parser -> status = FREE;
    parser -> size = 0;

    return OK;
}
