#ifndef STACK_INFO
#define STACK_INFO
#define GETLINE __LINE__
#define GETFUNCTION __func__
#define GETFILE __FILE__
#define GETNAME(a) #a
#include "errors.h"

#ifdef DOUBLE
typedef double data_type;
#define VANGUARD 0xDEADC0DEBAADF00DULL
#define REARGUARD 0xBADCAFE1BADB0015ULL
#define POISON_VALUE 6666.66666
#define ARR_VANGUARD 7777.77777
ERROR_CODES print_double(void * data_el_ptr);
ERROR_CODES fprintf_double(void * data_el_ptr, FILE * log);
#endif



#endif
