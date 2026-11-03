#include "../h/errors.h"


const char * ERROR_MESSAGES[11] = {
    "ERROR Unknown error in cpu",
    "ERROR finding command",
    "ERROR opening file",
    "ERROR null ptr",
    "ERROR ip out of range",
    "ERROR unknown argument",
    "ERROR unknown label",
    "ERROR no such register",
    "ERROR pushing",
    "ERROR popping",
    "ERROR unreachable jump"
};


int ErrorPuts(STATES_CPU error_code, const char * filename, const char * function_name, size_t line){
    printf("ERROR OCCURRED! ERRRO CODE : %d\n", error_code);
    puts(ERROR_MESSAGES[abs(error_code) - 1]);
    printf("ERROR IN FILE : %s\n", filename);
    printf("ERROR IN FUNC : %s\n", function_name);
    printf("ERROR IN LINE : %zu\n", line);
    return 0;
}

