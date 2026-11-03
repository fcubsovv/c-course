#ifndef ERRORS_
#define ERRORS_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cerrno>
#include <cstring>

enum  ERROR_CODES_STACK {//docs
    null_ptr_stack = 0,
    null_ptr_to_struct_stack,
    // Stack errors
    stack_data_interruption_start,
    stack_data_interruption_end,
    invalid_vanguard,
    invalid_rearguard,
    zero_capacity_stack,
    zero_size_stack,
    size_bigger_than_capacity,
    no_info_abt_stack_var_name,
    no_info_abt_stack_file,
    no_info_abt_creator_function,
    no_info_abt_stack_line,
    invalid_time_data,
    // OS errors
    cannot_open_file_stack,
    cannot_get_time_stack,
    cannot_get_time_info_stack,
    cannot_format_time_stack,
    cannot_close_log_file_stack,
    memory_allocation_error_stack,
    invalid_struct_hash,
    invalid_data_hash,
    allright_stack
};

struct errors {
    ERROR_CODES_STACK error_code;
    const char * error_message;
};


const errors ERRORS[] = {
    {null_ptr_stack, "null ptr"},
    {null_ptr_to_struct_stack, "null ptr to struct"},
    {stack_data_interruption_start, "stack data interruption start"},
    {stack_data_interruption_end, "stack data interruption end"},
    {invalid_vanguard, "invalid vanguard"},
    {invalid_rearguard, "invalid rearguard"},
    {zero_capacity_stack, "zero capacity"},
    {zero_size_stack, "zero stack size"},
    {size_bigger_than_capacity, "size bigger than capacity"},
    {no_info_abt_stack_var_name, "no info abt stack varname"},
    {no_info_abt_stack_file, "no info abt stack file"},
    {no_info_abt_creator_function, "no info abt creator function"},
    {no_info_abt_stack_line, "no info about stack line"},
    {invalid_time_data, "invalid stack time data"},
    {cannot_open_file_stack, "cannot open file"},
    {cannot_get_time_stack, "cannot get time"},
    {cannot_get_time_info_stack, "cannot get time info"},
    {cannot_format_time_stack, "cannot format time"},
    {cannot_close_log_file_stack, "cannot close log fi;e"},
    {memory_allocation_error_stack, "memory allocartion error"},
    {invalid_struct_hash, "invalid struct hash"},
    {invalid_data_hash, "invalid data hash"},
    {allright_stack, "allright_stack"},
};


ERROR_CODES_STACK ErrorDump(ERROR_CODES_STACK error_code, const char * function, const char * file, int line, const char * error_message);



#endif
