#include "../h/errors.h"

//open-close error logs  - open in main?? hard codede name(((())))-global const

const char * ERROR_FILE_NAME = "error_logger.log";


ERROR_CODES_STACK ErrorDump(ERROR_CODES_STACK error_code, const char * function, const char * file, int line, const char * error_message) {

    fprintf(stderr, "%s: %s\n", error_message, strerror(errno));
    fprintf(stderr, "in : %s in %d line in %s() \n", file, line, function);

    FILE * log = fopen(ERROR_FILE_NAME, "a");
    if (log == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        fprintf(stderr, "in : %s in %d line in %s() \n", file, line, function);
        return cannot_open_file_stack;
    }

    fprintf(log, "==========ERROR OCCURRED============\n");
    fprintf(log, "ERROR CODE: %d\n", error_code);
    fprintf(log, "ERROR MESSAGE: %s\n", ERRORS[error_code].error_message );
    fprintf(log,"in : %s in %d line in %s() \n", file, line, function);
    fprintf(log, "================END=================\n");

    fclose(log);
    if(fclose(log) != 0) {
        fprintf(stderr, "Error closing stack log file%s\n", strerror(errno));
        fprintf(stderr,"in : %s in %d line in %s() \n", file, line, function);
        return cannot_close_log_file_stack;
    }

    return allright_stack;
}
