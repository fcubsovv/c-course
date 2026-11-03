#include "../h/errors.h"


char ERROR_MESSAGES[11][64] = {
    "Unknown error in cpu",
    "Error finding command",
    "Error opening file",
    "Error null ptr",
    "Error ip out of range",
    "Error unknown argument",
    "Error unknown label",
    "Error no such register",
    "Error pushing",
    "Error popping",
    "Error unreachable jump"
};


int ErrorPuts(STATES_CPU error_code, const char * filename, const char * function_name, size_t line){
    printf("ERROR OCCURRED! ERRRO CODE : %d\n", error_code);
    puts(ERROR_MESSAGES[abs(error_code) - 1]);
    printf("ERROR IN FILE : %s\n", filename);
    printf("ERROR IN FUNC : %s\n", function_name);
    printf("ERROR IN LINE : %zu\n", line);
    return 0;
}

