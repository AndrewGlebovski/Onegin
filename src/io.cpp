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
 * \param [out] buffer Char array to change
 * \param [in] old_char This symbol will be replaced
 * \param [in] new_char This symbol will be set
 * \return Count of replacement
*/
int replace_in_buffer(char *buffer, const char old_char, const char new_char);


/**
 * \brief Reads file into buffer
 * \param [in] stream File to read from
 * \param [out] buffer Pointer to char array
 * \param [in] size Amount chars to read
 * \return In case of error returns #EXIT_CODE and buffer will be NULL otherwise actual number of read chars
*/
size_t read_in_buffer(FILE *stream, char **buffer, size_t size);


int read_viewer(StringViewer *viewer, FILE *stream) {
    ASSERT_AND_LOG(viewer, INVALID_ARGUMENT, "StringViewer was NULL", return INVALID_ARGUMENT);
    ASSERT_AND_LOG(stream, INVALID_ARGUMENT, "File was NULL", return INVALID_ARGUMENT);

    size_t size = get_file_size(stream);

    char *text = NULL;

    size = read_in_buffer(stream, &text, size);

    ASSERT_AND_LOG(text, (int) size, "read_in_buffer() returned error, retranslate it", return (int) size);

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


size_t read_in_buffer(FILE *stream, char **buffer, size_t size) {
    ASSERT_AND_LOG(!*buffer, INVALID_ARGUMENT, "Buffer points at something", return INVALID_ARGUMENT);

    *buffer = (char *) calloc(size + 1, sizeof(char));
    ASSERT_AND_LOG(*buffer, ALLOCATE_FAIL, "Not enough memory for buffer", return ALLOCATE_FAIL);

    ASSERT_AND_LOG(!setvbuf(stream, NULL, _IOFBF, size), BUFFER_ERROR, "Set buffer to file size returns error", free(*buffer); *buffer = NULL; return BUFFER_ERROR);

    size = fread(*buffer, sizeof(char), size, stream);
    ASSERT_AND_LOG(!ferror(stream), FILE_READ_ERROR, "Error while reading file", free(*buffer); *buffer = NULL; return FILE_READ_ERROR);

    ASSERT_AND_LOG(!setvbuf(stream, NULL, _IONBF, 0), BUFFER_ERROR, "Set buffer 0 returns error", free(*buffer); *buffer = NULL; return BUFFER_ERROR);

    *buffer = (char *) realloc(*buffer, size + 1);
    ASSERT_AND_LOG(*buffer, ALLOCATE_FAIL, "Reallocate buffer fail", return ALLOCATE_FAIL);

    (*buffer)[size] = '\0';

    return size;
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
