#include "../h/errors.h"

LIST_ERRORS DisplayListErrorInner(LIST_ERRORS error_code, const char * file, int line, const char * func) {
    if (error_code == allright_list || error_code == pop_empty_list || error_code == tryind_insert_beyond_limits) return allright_list;

    puts(  "ERROR HAPPENED!");
    printf("ERROR CODE: %d\n", error_code);
    printf("ERROR MESSAGE: %s\n",  LIST_ERROR_MESSAGES[error_code]);
    printf("AT: %s:%d (%s)\n", file, line, func);
    return error_code;
}
