#ifndef STACK_INFO
#define STACK_INFO

#define GETLINE __LINE__
#define GETFUNCTION __func__
#define GETFILE __FILE__
#define GETNAME(a) #a
#define VANGUARD 0xDEADC0DEBAADF00DULL
#define REARGUARD 0xBADCAFE1BADB0015ULL
#define POISON_VALUE 6666.66666
#define ARR_VANGUARD 7777.77777
#include "errors.cpp"

ERROR_CODES print_double(void * data_el_ptr) {
    if (data_el_ptr == NULL) {
        ErrorDump(null_ptr, GETFILE, GETFUNCTION, GETLINE, "Null ptr to data_el_ptr");
        return null_ptr;
    }
    double data_el = *(double *)data_el_ptr;
    printf("%lg ", (double)data_el);
    return allright;
}

ERROR_CODES fprintf_double(void * data_el_ptr, FILE * log) {
    if (data_el_ptr == NULL) {
        ErrorDump(null_ptr, GETFILE, GETFUNCTION, GETLINE, "Null ptr to data_el_ptr");
        return null_ptr;
    }
    if (log == NULL) {
        ErrorDump(null_ptr, GETFILE, GETFUNCTION, GETLINE, "Null ptr to log file");
        return null_ptr;
    }
    double data_el = *(double *)data_el_ptr;
    fprintf(log, "%lg ", data_el);
    return allright;
}


#endif






