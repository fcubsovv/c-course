#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cerrno>
#include <cstring>
#include "../h/tests.h"

#include "../h/_STACK_.h"
//atexit
//
//check можно ли по этому указателю что то записать которая читает состояние памяти
//hash fucntion using address for stack, for stack.data
//docs for errors
//capacity......

const char * filename = "test.log";

int main (int args, const char * argv[]) {

    FILE * log = fopen(filename, "a");
    if (log == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        fprintf(stderr, "in : %s in %d line in %s() \n", (char*)GETFILE, GETLINE, (char*)GETFUNCTION);
        return cannot_open_file;
    }

//------------null ptrs-------------
    StackTestNullPtrs(log);

//-----------data vanguards---------------
    StackTestDataGuards(log);

//-----------struct vanguards--------------
    StackTestGuards(log);

//------------data hash-------------------
    StackTestHashesTest(log);

//-----------allright test---------------
    if (fclose(log) != 0) {
        fprintf(stderr, "Error closing stack log file%s\n", strerror(errno));
        fprintf(stderr, "in : %s in %d line in %s() \n", (char*)GETFILE, GETLINE, (char*)GETFUNCTION);
        return cannot_close_log_file;
    }
    return 0;
}



