#include "h/filework.h"

buffer_struct ReadFromFileToBuffer(const char * file_name) {
    buffer_struct answer = {
        NULL,
        0
    };
    int file = open(file_name, O_RDONLY, 0);
    if (file == -1) {
        perror("cant open input file");
        return answer;
    }
    struct stat buff;
    fstat(file, &buff);
    size_t nitems = buff.st_size;
    unsigned char * buffer = (unsigned char *) calloc(nitems+1, sizeof(char));
    if (buffer == NULL) {
        perror("error in memory usage for text");
        return answer;
    }
    int read_result = read(file, buffer, nitems);
    if (read_result == -1 || read_result != nitems) {
        perror("error in reading input file");
        return answer;
    }
    int close_result = close(file);
    if (close_result != 0) {
        perror("error in closing file occured");
    }
    answer = {
        buffer,
        nitems
    };
    return answer;
}

