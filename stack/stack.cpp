#ifndef STACK
#define STACK
#include "stack_info.cpp"
#include <stdio.h>
#include <inttypes.h>
typedef double data_type;
#include "errors.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include "crc32.cpp"


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

int PrintStack(stack * stack, ERROR_CODES printer(void *)) {
    for (size_t i = 0; i < stack->capacity + 2; i++) {
        printer(&stack->data[i]);
    }
    return 0;
}

ERROR_CODES FprintfStack(const stack * stack, FILE * log, ERROR_CODES fprinter(void *, FILE *)) {
    if (stack == NULL) {
        return null_ptr_to_struct;
    }
    char time_str[20] = {};
    size_t result = strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S",  &stack->timeinfo);
    if (result == 0) {
        ErrorDump(cannot_format_time, GETFILE, GETFUNCTION, GETLINE, "Cannot format time info, not enough place in buffer");
        return cannot_format_time;
    }

    fprintf(log, "STACK ENTRAILS: \n");
    fprintf(log, "---->STACK SIZE: %zu \n", stack->size);
    fprintf(log, "---->STACK CAPACITY: %zu\n", stack->capacity);
    fprintf(log, "---->STACK VARIABLE NAME %s\n", stack->stack_variable);
    fprintf(log, "---->STACK DATA HASH 0x%" PRIx32 "\n", stack->data_hash);
    fprintf(log, "---->STACK STRUCT HASH 0x%" PRIu32 "\n", stack->struct_hash);
    fprintf(log, "---->STACK: \n");
    fprintf(log, "------>STACK DATA = ");//
    for (size_t i = 1; i < stack->capacity; i++) {
        ERROR_CODES res = fprinter(&stack->data[i], log);
    }
    fprintf(log, "\n");
    fprintf(log, "---->VANGUARD: 0x%llx\n", (unsigned long long)stack->vanguard);
    fprintf(log, "---->REARGUARD: 0x%llx\n", (unsigned long long)stack->rearguard);
    fprintf(log, "STACK WAS CREATED IN : %s in %s() in %d line\n", stack->created_in_file, stack->created_by_function, stack->line);
    fprintf(log, "STACK WAS CREATED AT: [%s] \n", time_str);
    return allright;
}

ERROR_CODES CheckStack(const stack * stack) {
    if (stack == NULL) {
        return null_ptr_to_struct;
    }
    if (stack->vanguard != (VANGUARD ^ (uintptr_t)stack)) {
        return invalid_vanguard;
    }
    if(stack->rearguard != (REARGUARD ^ (uintptr_t)stack)) {
        return invalid_rearguard;
    }
    if(stack->data[0] != ARR_VANGUARD) {
        return stack_data_interruption_start;
    }
    if (stack->struct_hash !=  CalculateCRC32(stack, offsetof(struct stack, struct_hash))) {
        return invalid_struct_hash;
    }
    if (stack->data_hash !=  CalculateCRC32(stack->data, sizeof(data_type) * (stack->capacity+2))) {
        return invalid_data_hash;
    }
    if (stack->capacity == 0) {
        return zero_capacity;
    }
    if(stack->size > stack->capacity) {
        return size_bigger_than_capacity;
    }
    for (size_t i = stack->size+1; i < stack->capacity+2; i++) {
        if (stack->data[i] != POISON_VALUE) {
            return stack_data_interruption_end;
        }
    }
    if(stack->stack_variable == NULL) {
        return no_info_abt_stack_var_name;
    }
    if(stack->created_in_file == NULL) {
        return no_info_abt_stack_file;
    }
    if(stack->created_by_function == NULL) {
        return no_info_abt_creator_function;
    }
    if(stack->line == 0){
        return no_info_abt_stack_line;
    }
    if(stack->timeinfo.tm_year == 0) {
        return invalid_time_data;
    }
    return allright;
}

ERROR_CODES StackDump(const stack * stack, const char * file, int line, const char * func, ERROR_CODES code, ERROR_CODES fprint_stack_el(void *, FILE *)) {
    FILE * log = fopen("stack_debug.log", "a");
    if (log == NULL) {
        ErrorDump(cannot_open_file, GETFILE, GETFUNCTION, GETLINE, "Error opening file");
        return cannot_open_file;
    }
    time_t time_ = time(NULL);
    if (time_ == (time_t)-1) {
        ErrorDump(cannot_get_time, GETFILE, GETFUNCTION, GETLINE, "Error getting the time");
        return cannot_get_time;
    }
    struct tm * timeinfo = localtime(&time_);
    if (timeinfo == NULL) {
        ErrorDump(cannot_get_time_info, GETFILE, GETFUNCTION, GETLINE, "Cannot get time info, cannot convert time format");
        return cannot_get_time_info;
    }
    char time_str[20] = {};
    size_t result = strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    if (result == 0) {
        ErrorDump(cannot_format_time, GETFILE, GETFUNCTION, GETLINE, "Cannot format time info, not enough place in buffer");
        return cannot_format_time;
    }
    fprintf(log, "==========ERROR OCCURRED============\n");
    fprintf(log, "ERROR CODE: %d\n", code);
    fprintf(log, "ERROR MESSAGE: %s\n", ERRORS[code].error_message );
    fprintf(log, "at : [%s] \n", time_str);
    fprintf(log,"in : %s in %d line in %s() \n", file, line, func);
    FprintfStack(stack, log, fprint_stack_el);
    fprintf(log, "================END=================\n");
    if(fclose(log) != 0) {
        ErrorDump(cannot_close_log_file, GETFILE, GETFUNCTION, GETLINE, "Error closing stack log file");
        return cannot_close_log_file;
    }
    return allright;
}

#endif
