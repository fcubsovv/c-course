#ifndef ERRORS_CPU
#define ERRORS_CPU
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GETFILE_CPU(x) __FILE__
#define GETFUNCTION_CPU(x) __func__
#define GETLINE_CPU(x) __LINE__


int ErrorPuts(STATES_CPU error_code, const char * filename, const char * function_name, size_t line);

#endif
