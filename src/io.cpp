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


/**
 * \brief Replaces specific character in string 
 * \param [out] buffer Array to change
 * \param [in] old_char This symbol will be replaced
 * \param [in] new_char This symbol will be set
 * \return Count of replacement
*/
int replace_in_buffer(char *buffer, const char old_char, const char new_char);


int read_viewer(StringViewer *viewer, FILE *stream) {
    ASSERT_AND_LOG(viewer, INVALID_ARGUMENT, "StringViewer was NULL", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(stream, INVALID_ARGUMENT, "File was NULL",         return INVALID_ARGUMENT);

    size_t size = get_file_size(stream);

    char *text = (char *) calloc(size + 1, sizeof(char));
    ASSERT_AND_LOG(text, ALLOCATE_FAIL, "Not enough memory for text", return ALLOCATE_FAIL);

    ASSERT_AND_LOG(!setvbuf(stream, NULL, _IOFBF, size), BUFFER_ERROR, "Set buffer to file size returns error", free(text); viewer -> status = FREE; return BUFFER_ERROR);

    size = fread(text, sizeof(char), size, stream);
    ASSERT_AND_LOG(!ferror(stream), FILE_READ_ERROR, "Error while reading file", free(text); viewer -> status = FREE; return FILE_READ_ERROR);

    ASSERT_AND_LOG(!setvbuf(stream, NULL, _IONBF, 0), BUFFER_ERROR, "Set buffer 0 returns error", free(text); viewer -> status = FREE; return BUFFER_ERROR);

    text = (char *) realloc(text, size + 1);
    ASSERT_AND_LOG(text, ALLOCATE_FAIL, "Reallocate text fail", return ALLOCATE_FAIL);

    text[size] = '\0';
    int lines = 1 + replace_in_buffer(text, '\n', '\0');

    viewer -> lines = (String *) calloc(lines + 1, sizeof(String));

    ASSERT_AND_LOG(viewer -> lines, ALLOCATE_FAIL, "Not enough memory for lines", free(text); viewer -> status = FREE; return ALLOCATE_FAIL);

    viewer -> text = text;

    for(int l = 0; l < lines; l++) {
        (viewer -> lines)[l] = {text, 0};

        while(*text != '\0')
            text++;

        (viewer -> lines)[l].len = (int)(text - (viewer -> lines)[l].str);

        text++;
    }

    (viewer -> lines)[lines] = {nullptr, -1};
    viewer -> size = lines;

    viewer -> status = FILL;

    return OK;
}


int replace_in_buffer(char *buffer, const char old_char, const char new_char) {
    ASSERT_AND_LOG(buffer, INVALID_ARGUMENT, "Buffer was NULL", return -1);

    int count = 0;
    for(size_t i = 0; buffer[i]; i++) {
        if (buffer[i] == old_char) {
            buffer[i] = new_char;
            count++;
        }
    }
    return count;
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

    free(viewer -> lines);
    free(viewer -> text);

    viewer -> status = FREE;
    viewer -> size = 0;

    return OK;
}
