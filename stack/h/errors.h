#ifndef ERRORS_
#define ERRORS_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cerrno>
#include <cstring>

enum  ERROR_CODES{//docs
    null_ptr = 0,
    null_ptr_to_struct,
    // Stack errors
    stack_data_interruption_start,
    stack_data_interruption_end,
    invalid_vanguard,
    invalid_rearguard,
    zero_capacity,
    zero_size,
    size_bigger_than_capacity,
    no_info_abt_stack_var_name,
    no_info_abt_stack_file,
    no_info_abt_creator_function,
    no_info_abt_stack_line,
    invalid_time_data,
    // OS errors
    cannot_open_file,
    cannot_get_time,
    cannot_get_time_info,
    cannot_format_time,
    cannot_close_log_file,
    memory_allocation_error,
    invalid_struct_hash,
    invalid_data_hash,
    allright
};

struct errors {
    ERROR_CODES error_code;
    const char * error_message;
};


const errors ERRORS[] = {
    {null_ptr, "null ptr"},
    {null_ptr_to_struct, "null ptr to struct"},
    {stack_data_interruption_start, "stack data interruption start"},
    {stack_data_interruption_end, "stack data interruption end"},
    {invalid_vanguard, "invalid vanguard"},
    {invalid_rearguard, "invalid rearguard"},
    {zero_capacity, "zero capacity"},
    {zero_size, "zero stack size"},
    {size_bigger_than_capacity, "size bigger than capacity"},
    {no_info_abt_stack_var_name, "no info abt stack varname"},
    {no_info_abt_stack_file, "no info abt stack file"},
    {no_info_abt_creator_function, "no info abt creator function"},
    {no_info_abt_stack_line, "no info about stack line"},
    {invalid_time_data, "invalid stack time data"},
    {cannot_open_file, "cannot open file"},
    {cannot_get_time, "cannot get time"},
    {cannot_get_time_info, "cannot get time info"},
    {cannot_format_time, "cannot format time"},
    {cannot_close_log_file, "cannot close log fi;e"},
    {memory_allocation_error, "memory allocartion error"},
    {invalid_struct_hash, "invalid struct hash"},
    {invalid_data_hash, "invalid data hash"},
    {allright, "allright"},
};


ERROR_CODES ErrorDump(ERROR_CODES error_code, const char * function, const char * file, int line, const char * error_message);



#endif
