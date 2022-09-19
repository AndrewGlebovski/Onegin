/**
 * \file
 * \brief Contains input and output functions
*/

#include <stdlib.h>
#include "onegin.hpp"


/**
 * \brief Returns file size in bytes
 * \param [in] stream File
 * \return Size in bytes
*/
size_t get_file_size(FILE *stream);


int read_viewer(StringViewer *viewer, FILE *stream) {
    ASSERT_AND_LOG(viewer, INVALID_ARGUMENT, "StringViewer was NULL", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(stream, INVALID_ARGUMENT, "File was NULL", return INVALID_ARGUMENT);

    size_t size = get_file_size(stream);

    char *storage = (char *) calloc(size, sizeof(char));

    viewer -> text = storage;

    ASSERT_AND_LOG(viewer -> text, ALLOCATE_FAIL, "Not enough memory for text", return ALLOCATE_FAIL);

    int lines = 0;

    size = fread(storage, sizeof(char), size, stream);
    storage = (char *) realloc(storage, size);

    for(size_t i = 0; i < size; i++) {
        if (storage[i] == '\n') {
            storage[i] = '\0';
            lines++;
        }
    }

    viewer -> lines = (String *) calloc(lines + 1, sizeof(String));

    ASSERT_AND_LOG(viewer -> lines, ALLOCATE_FAIL, "Not enough memory for lines", return ALLOCATE_FAIL);

    for(int l = 0; l < lines; l++) {
        (viewer -> lines)[l] = {storage, 0};

        while(*storage != '\0')
            storage++;

        (viewer -> lines)[l].len = (int)(storage - (viewer -> lines)[l].str);

        storage++;
    }

    (viewer -> lines)[lines] = {nullptr, -1};
    viewer -> size = lines;

    viewer -> status = FILL;

    return OK;
}


size_t get_file_size(FILE *stream) {
    fseek(stream, 0, SEEK_END);
    size_t size = ftell(stream);
    rewind(stream);
    return size;
}


int print_lines(String lines[], FILE *stream) {
    ASSERT_AND_LOG(lines, INVALID_ARGUMENT, "Lines was null", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(stream, INVALID_ARGUMENT, "File was NULL", return INVALID_ARGUMENT);

    for(int i = 0; lines[i].str != nullptr && lines[i].len != -1; i++) {
        fprintf(stream, "%s\n", lines[i].str);
        fflush(stream);
    }

    return OK;
}


int free_viewer(StringViewer *viewer) {
    ASSERT_AND_LOG(viewer, INVALID_ARGUMENT, "StringViewer was NULL", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(viewer -> status == FILL, INVALID_ARGUMENT, "Double free is not allowed", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(viewer -> text, INVALID_ARGUMENT, "Text was NULL", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(viewer -> lines, INVALID_ARGUMENT, "Lines was NULL", return INVALID_ARGUMENT);

    free(viewer -> text);
    free(viewer -> lines);

    viewer -> status = FREE;
    viewer -> size = 0;

    return OK;
}
