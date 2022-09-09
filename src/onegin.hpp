#include <stdio.h>


const int MAX_LINES = 1000;
const int MAX_LENGTH = 100;


void sort_poem(char *poem[], unsigned int poem_size);


int read_poem(char *poem[], FILE *stream);


void print_poem(char *poem[], FILE *stream);
