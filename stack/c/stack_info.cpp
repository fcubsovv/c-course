#include "../h/stack_info.h"
//-------------------------------------------------------------------------------------------------------------------

ERROR_CODES_STACK print_double(void * data_el_ptr) {
    if (data_el_ptr == NULL) {
        ErrorDump(null_ptr_stack, GETFILE, GETFUNCTION, GETLINE, "Null ptr to data_el_ptr");
        return null_ptr_stack;
    }
    double data_el = *(double *)data_el_ptr;
    printf("%lg ", (double)data_el);
    return allright_stack;
}

ERROR_CODES_STACK fprintf_double(void * data_el_ptr, FILE * log) {
    if (data_el_ptr == NULL) {
        ErrorDump(null_ptr_stack, GETFILE, GETFUNCTION, GETLINE, "Null ptr to data_el_ptr");
        return null_ptr_stack;
    }
    if (log == NULL) {
        ErrorDump(null_ptr_stack, GETFILE, GETFUNCTION, GETLINE, "Null ptr to log file");
        return null_ptr_stack;
    }
    double data_el = *(double *)data_el_ptr;
    fprintf(log, "%lg ", data_el);
    return allright_stack;
}

//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------






