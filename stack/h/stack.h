#ifndef STACK
#define STACK

#include <stdio.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cerrno>
#include <cstring>

#include "type.h"

#ifndef TYPE
    #define TYPE
    #define DOUBLE
    typedef double data_type;
#endif

#include "crc32.h"
#include "stack_info.h"

struct stack {
    uintptr_t vanguard;
    data_type * data;
    size_t capacity;
    size_t size;
    char * created_by_function;
    char * created_in_file;
    char * stack_variable;
    int line;
    tm timeinfo;
    uint32_t data_hash;
    uint32_t struct_hash;
    uintptr_t rearguard;
};

ERROR_CODES_STACK PrintStack(stack * stack, ERROR_CODES_STACK printer(void *))  ;

ERROR_CODES_STACK FprintfStack(const stack * stack, FILE * log, ERROR_CODES_STACK fprinter(void *, FILE *)) ;

ERROR_CODES_STACK CheckStack(const stack * stack) ;

ERROR_CODES_STACK DumpStack(const stack * stack, const char * file, int line, const char * func, ERROR_CODES_STACK code, ERROR_CODES_STACK fprint_stack_el(void *, FILE *)) ;

#endif
