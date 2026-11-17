#ifndef FILEWORK
#define FILEWORK
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct buffer_struct {
    unsigned char * buffer;
    size_t nitems;
};


buffer_struct ReadFromFileToBuffer(const char * file_name);





#endif
