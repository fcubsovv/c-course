#ifndef STACK_UTILS
#define STACK_UTILS

#include "stack.h"
#include "_MODE_.h"

#ifdef DEBUG
    #define STACK_LOG(stack) \
        if (CheckStack(stack) != allright_stack) DumpStack(stack, __FILE__, __LINE__, __func__, CheckStack(stack), fprintf_double)
#elif defined(LOGGING)
    #define STACK_LOG(stack) \
        DumpStack(stack, __FILE__, __LINE__, __func__, CheckStack(stack), fprintf_double)
#else
    #define STACK_LOG(stack)
#endif

ERROR_CODES_STACK StackPush(stack * stack, data_type element);

ERROR_CODES_STACK StackPop(stack * stack, data_type * popped_el) ;

ERROR_CODES_STACK StackConstructor (stack * stack, const char * varname, const char * function_called_constructor, const char * file_called_constructor);

ERROR_CODES_STACK StackDestructor(stack * stack);

ERROR_CODES_STACK StackCopy(const stack * original, stack * parody,  const char * function_called_copy, const char * file_called_copy, const char * varname) ;

#define STACK_CONSTRUCTOR(stack) StackConstructor (stack, #stack, (char*)__func__, (char*) __FILE__);
#define STACK_COPY(original, parody) StackCopy(original, parody, (char*) __func__, (char*)__FILE__, #parody);

#endif
