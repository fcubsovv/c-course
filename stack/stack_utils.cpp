#ifndef STACK_UTILS
#define STACK_UTILS
#include "errors.cpp"
#include "stack.cpp"
#include "stack_info.cpp"
#include "assert.h"
#include "crc32.cpp"


#ifdef DEBUG
    #define STACK_LOG(stack) \
        if (CheckStack(stack) != allright) StackDump(stack, __FILE__, __LINE__, __func__, CheckStack(stack), fprintf_double)
#elif defined(LOGGING)
    #define STACK_LOG(stack) \
        StackDump(stack, __FILE__, __LINE__, __func__, CheckStack(stack), fprintf_double)
#else
    #define STACK_LOG(stack)
#endif



ERROR_CODES StackPush(stack * stack, data_type element) {//FIX
    STACK_LOG(stack);
    ERROR_CODES code = CheckStack(stack);
    if (code != allright) {
        return code;
    }
    printf("element %lg\n",   element);
    printf("element %lg\n",   element);
    if (stack->size >= stack->capacity) {
        stack->capacity*=2;
        data_type * arr = (data_type *)realloc(stack->data, (stack->capacity + 2) * sizeof(data_type));

        if (arr == NULL) {
            return memory_allocation_error;
        }
        stack->data = arr;
        for (size_t i = stack->size+1; i < stack->capacity + 2; i++) {
            stack->data[i] = POISON_VALUE;
        }

    }
    stack->data[stack->size + 1] = element;
    stack->size+=1;
    stack->data_hash =  CalculateCRC32(stack->data, sizeof(data_type) * (stack->capacity+2));
    stack->struct_hash =  CalculateCRC32(stack, offsetof(struct stack, struct_hash));
    code = CheckStack(stack);
    if (code != allright) {
        return code;
    }
    return allright;
}





ERROR_CODES StackPop(stack * stack) {
    STACK_LOG(stack);
    ERROR_CODES code = CheckStack(stack);
    if (code != allright) {
        return code;
    }
    if (stack->size == 0) {
        return zero_size;
    }
    stack->data[stack->size] = POISON_VALUE;
    stack->size-=1;
    if (stack->size < stack->capacity/2) {
        stack->capacity/=2;
        data_type * arr = (data_type *)realloc(stack->data, (stack->capacity + 2) * sizeof(data_type));
        if (arr == NULL) {
            return memory_allocation_error;
        }
        stack->data = arr;
        for (size_t i = stack->size+1; i < stack->capacity + 2; i++) {
            stack->data[i] = POISON_VALUE;
        }
    }
    stack->data_hash = CalculateCRC32(stack->data, sizeof(data_type) * (stack->capacity + 2));
    stack->struct_hash = CalculateCRC32(stack, offsetof(struct stack, struct_hash));
    STACK_LOG(stack);
    code = CheckStack(stack);
    if (code != allright) {
        return code;
    }
    return allright;
}

ERROR_CODES StackConstructor (stack * stack, char * varname, char * function_called_constructor, char * file_called_constructor) {//FIX timecheck function
    STACK_LOG(stack);
    if (stack == NULL) return null_ptr_to_struct;
    stack->capacity = 8;
    stack->size = 0;
    data_type * arr = (data_type *)calloc((stack->capacity + 2), sizeof(data_type));
    if (arr == NULL) {
        return memory_allocation_error;
    }
    stack->data = arr;
    for (size_t i = 1; i < stack->capacity + 2; i++) {
        stack->data[i] = POISON_VALUE;
    }
    stack->data[0] = ARR_VANGUARD;
    stack->line = GETLINE;
    stack->created_by_function = function_called_constructor;
    stack->created_in_file = file_called_constructor;
    stack->stack_variable = varname;

    uintptr_t struct_canary_start = VANGUARD ^ (uintptr_t)stack;
    uintptr_t struct_canary_end = REARGUARD ^ (uintptr_t)stack;
    stack->vanguard  = struct_canary_start;
    stack->rearguard = struct_canary_end;

    time_t time_ = time(NULL);//timecheck
    struct tm *timeinfo = localtime(&time_);
    stack->timeinfo = *timeinfo;

    stack->data_hash =  CalculateCRC32(stack->data, sizeof(data_type) * (stack->capacity+2));//xooor
    stack->struct_hash = CalculateCRC32(stack, offsetof(struct stack, struct_hash));

    STACK_LOG(stack);
    ERROR_CODES code = CheckStack(stack);
    if (code != allright) {
        return code;
    }

    return allright;

}


ERROR_CODES StackDestructor(stack * stack) {
    STACK_LOG(stack);
    if (stack == NULL) return null_ptr_to_struct;
    ERROR_CODES code = CheckStack(stack);
    if (code != allright) {
        return code;
    }
    if (stack->data != NULL) {
        for (size_t i = 0; i < stack->capacity + 2; i++) {
            stack->data[i] = POISON_VALUE;
        }
        free(stack->data);
        stack->data = NULL;
    }
    stack->capacity = 0;
    stack->size = 0;
    stack->line = -1;
    stack->created_by_function = NULL;
    stack->created_in_file     = NULL;
    stack->stack_variable      = NULL;
    stack->struct_hash         = 0;
    stack->data_hash           = 0;
    memset(&stack->timeinfo, 0, sizeof(tm));
    stack->vanguard  = 0xDEADBEEF;
    stack->rearguard = 0xDEADBEEF;
    return allright;
}

ERROR_CODES CopyStack(const stack * original, stack * parody,  char * function_called_copy, char * file_called_copy, char * varname) {
    STACK_LOG(original);
    ERROR_CODES code = CheckStack(original);
    if (code != allright) {
        return code;
    }
    if (parody == NULL) return null_ptr_to_struct;

    StackConstructor(parody, varname, function_called_copy, file_called_copy);
    for (size_t i = 1; i < original->size+1; i++) {
        printf("%lg\n", original->data[i]);
        StackPush(parody, original->data[i]);
    }
    parody->data_hash =  CalculateCRC32(parody->data, sizeof(data_type) * (parody->capacity+2));//xooor
    parody->struct_hash = CalculateCRC32(parody, offsetof(struct stack, struct_hash));

    STACK_LOG(parody);
    ERROR_CODES code_ = CheckStack(parody);
    if (code_ != allright) {
        return code_;
    }

    return allright;
}

#endif
