/**
 * \file io.cpp
 * \brief Contains input and output functions
*/

#include <stdlib.h>
#include "onegin.hpp"


int read_poem(StringPointer **poem, FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    int lines = 0, chars = 0;
    char line[100];
    while(fgets(line, 1000, stream) != NULL) 
        lines++;

    chars = ftell(stream);

    rewind(stream);

    *poem = (StringPointer *) calloc(lines + 1, sizeof(StringPointer));

    char *storage = (char *) calloc(chars, sizeof(char));

    for(int l = 0; l < lines; l++) {
        (*poem)[l] = {storage, 0};
        int c = 0;

        while((c = fgetc(stream)) != '\n')
            *storage++ = (char) c;

        (*poem)[l].len = (int)(storage - (*poem)[l].str);
        
        *storage++ = '\0';
    }

    (*poem)[lines] = {nullptr, -1}; 

    return lines;
}


void print_poem(StringPointer poem[], FILE *stream) {
    if (!stream)
        printf("File pointer was null");

    for(int i = 0; poem[i].str != nullptr && poem[i].len != -1; i++) {
        fprintf(stream, "%s\n", poem[i].str);
        fflush(stream);
    }
}
