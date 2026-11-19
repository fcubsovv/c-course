#ifndef AKINATOR_ERRORS
#define AKINATOR_ERRORS
#include "tree_declaration.h"
#include <cstdio>

const char * const AKINATOR_ERROR_MESSAGES[] = {
    "ok",
    "unexpected behavior",
    "cannot open file",
    "null ptr to node",
    "invalid user input",
};


AKINATOR_TREE_ERRORS DisplayAkinatorErrorInner(AKINATOR_TREE_ERRORS error_code, const char * file, int line, const char * func);

#define DisplayAkinatorError(error_code) \
    DisplayAkinatorErrorInner((error_code), __FILE__, __LINE__, __func__)



#endif
