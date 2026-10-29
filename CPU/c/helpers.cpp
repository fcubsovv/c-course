#include "../h/helpers.h"

size_t count_lines_helper(buffer_struct read) {
    size_t lines = 0;
    for (size_t i = 0; i < read.nitems; i++) {
        if (read.buffer[i] == '\n') {
            lines ++;
        }
    }
    return lines;
}

