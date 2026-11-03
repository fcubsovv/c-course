#ifndef TESTS
#define TESTS
#include "errors.h"
#include "_STACK_.h"

ERROR_CODES_STACK StackTestNullPtrs(FILE * log);

ERROR_CODES_STACK StackTestGuards(FILE * log) ;

ERROR_CODES_STACK StackTestDataGuards(FILE * log) ;

ERROR_CODES_STACK StackTestHashesTest(FILE * log) ;

#endif
