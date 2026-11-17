#ifndef LIST_ERRORS_FILE
#define LIST_ERRORS_FILE
#include "list_decklaration.h"


const char * const LIST_ERROR_MESSAGES[] = {
    "ok",
    "cannot open file",
    "pop from empty list",
    "insert beyond limits",
    "memory allocation error",
    "pull beyond limits",
    "extra element in list",
    "prev/next mismatch",
    "tail error",
    "bad prev in free element",
    "capacity error",
    "head value error",
};


LIST_ERRORS DisplayListErrorInner(LIST_ERRORS error_code, const char * file, int line, const char * func);

#define DisplayListError(error_code) \
    DisplayListErrorInner((error_code), __FILE__, __LINE__, __func__)

#endif
