#include "../h/stack.h"


ERROR_CODES_STACK PrintStack(stack * stack, ERROR_CODES_STACK printer(void *)) {
    for (size_t i = 0; i < stack->capacity + 2; i++) {
        printer(&stack->data[i]);
    }
    return allright_stack;
}

ERROR_CODES_STACK FprintfStack(const stack * stack, FILE * log, ERROR_CODES_STACK fprinter(void *, FILE *)) {
    if (stack == NULL) {
        return null_ptr_to_struct_stack;
    }
    char time_str[20] = {};
    size_t result = strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S",  &stack->timeinfo);
    if (result == 0) {
        ErrorDump(cannot_format_time_stack, GETFILE, GETFUNCTION, GETLINE, "Cannot format time info, not enough place in buffer");
        return cannot_format_time_stack;
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
        ERROR_CODES_STACK res = fprinter(&stack->data[i], log);
    }
    fprintf(log, "\n");
    fprintf(log, "---->VANGUARD: 0x%llx\n", (unsigned long long)stack->vanguard);
    fprintf(log, "---->REARGUARD: 0x%llx\n", (unsigned long long)stack->rearguard);
    fprintf(log, "STACK WAS CREATED IN : %s in %s() in %d line\n", stack->created_in_file, stack->created_by_function, stack->line);
    fprintf(log, "STACK WAS CREATED AT: [%s] \n", time_str);
    return allright_stack;
}

ERROR_CODES_STACK CheckStack(const stack * stack) {///canary death hash death
    if (stack == NULL) {
        return null_ptr_to_struct_stack;
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
    if (stack->capacity == 0) {
        return zero_capacity_stack;
    }
    if(stack->size > stack->capacity) {
        return size_bigger_than_capacity;
    }
    for (size_t i = stack->size+1; i < stack->capacity+2; i++) {
        if (stack->data[i] != POISON_VALUE) {
            return stack_data_interruption_end;
        }
    }
    if (stack->struct_hash !=  CalculateCRC32(stack, offsetof(struct stack, struct_hash))) {
        return invalid_struct_hash;
    }
    if (stack->data_hash !=  CalculateCRC32(stack->data, sizeof(data_type) * (stack->capacity+2))) {
        return invalid_data_hash;
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
    return allright_stack;
}

ERROR_CODES_STACK DumpStack(const stack * stack, const char * file, int line, const char * func, ERROR_CODES_STACK code, ERROR_CODES_STACK fprint_stack_el(void *, FILE *)) {
    FILE * log = fopen("stack_debug.log", "a");
    if (log == NULL) {
        ErrorDump(cannot_open_file_stack, GETFILE, GETFUNCTION, GETLINE, "Error opening file");
        return cannot_open_file_stack;
    }
    time_t time_ = time(NULL);
    if (time_ == (time_t)-1) {
        ErrorDump(cannot_get_time_stack, GETFILE, GETFUNCTION, GETLINE, "Error getting the time");
        return cannot_get_time_stack;
    }
    struct tm * timeinfo = localtime(&time_);
    if (timeinfo == NULL) {
        ErrorDump(cannot_get_time_info_stack, GETFILE, GETFUNCTION, GETLINE, "Cannot get time info, cannot convert time format");
        return cannot_get_time_info_stack;
    }
    char time_str[20] = {};
    size_t result = strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    if (result == 0) {
        ErrorDump(cannot_format_time_stack, GETFILE, GETFUNCTION, GETLINE, "Cannot format time info, not enough place in buffer");
        return cannot_format_time_stack;
    }
    if (code == null_ptr_stack || code == null_ptr_to_struct_stack || code == stack_data_interruption_start || code == stack_data_interruption_end || code == invalid_vanguard || code == invalid_rearguard || code == invalid_struct_hash || code == invalid_data_hash) {
        fprintf(log, "==========ERROR OCCURRED============\n");
        fprintf(log, "ERROR CODE: %d\n", code);
        fprintf(log, "ERROR MESSAGE: %s\n", ERRORS[code].error_message );
        fprintf(log, "at : [%s] \n", time_str);
        fprintf(log,"in : %s in %d line in %s() \n", file, line, func);
        fprintf(log, "================END=================\n");
        return code;
    }
    fprintf(log, "==========ERROR OCCURRED============\n");
    fprintf(log, "ERROR CODE: %d\n", code);
    fprintf(log, "ERROR MESSAGE: %s\n", ERRORS[code].error_message );
    fprintf(log, "at : [%s] \n", time_str);
    fprintf(log,"in : %s in %d line in %s() \n", file, line, func);
    FprintfStack(stack, log, fprint_stack_el);
    fprintf(log, "================END=================\n");
    if(fclose(log) != 0) {
        ErrorDump(cannot_close_log_file_stack, GETFILE, GETFUNCTION, GETLINE, "Error closing stack log file");
        return cannot_close_log_file_stack;
    }
    return allright_stack;
}

