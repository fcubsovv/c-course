#include "../h/errors.h"

AKINATOR_TREE_ERRORS DisplayAkinatorErrorInner(AKINATOR_TREE_ERRORS error_code, const char * file, int line, const char * func) {

    if (error_code >=0 ) return akinator_allright;

    puts(  "ERROR HAPPENED!");
    printf("ERROR CODE: %d\n", error_code);
    printf("ERROR MESSAGE: %s\n",  AKINATOR_ERROR_MESSAGES[error_code]);
    printf("AT: %s:%d (%s)\n", file, line, func);
    return error_code;
}
