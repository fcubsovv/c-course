#ifndef TESTS
#define TESTS
#include "errors.h"
#include "_STACK_.h"

ERROR_CODES StackTestNullPtrs(FILE * log);

ERROR_CODES StackTestGuards(FILE * log) ;

ERROR_CODES StackTestDataGuards(FILE * log) ;

ERROR_CODES StackTestHashesTest(FILE * log) ;

#endif
