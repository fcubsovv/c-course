#ifndef FILEWORK
#define FILEWORK
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

struct buffer_struct {
    char * buffer;
    size_t nitems;
};

buffer_struct ReadFromFileToBuffer(char * file_name) {
    buffer_struct answer = {
        NULL,
        NULL
    };
    int file = open(file_name, O_RDONLY, 0);
    if (file == -1) {
        perror("cant open input file");
        return answer;
    }
    struct stat buff;
    fstat(file, &buff);
    size_t nitems = buff.st_size;
    char * buffer = (char *) calloc(nitems+1, sizeof(char));
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
#endif
