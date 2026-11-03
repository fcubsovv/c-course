#include "../h/tests.h"

ERROR_CODES_STACK StackTestNullPtrs(FILE * log) {
    ERROR_CODES_STACK ch1 = StackPush(NULL, 2);
    ERROR_CODES_STACK ch2 = StackPop(NULL, NULL);
    ERROR_CODES_STACK ch3 = StackCopy(NULL, NULL, (char*)GETFUNCTION, (char *)GETFILE, (char *)GETNAME(NULL));
    ERROR_CODES_STACK ch4 = StackConstructor(NULL, (char * )GETNAME(NULL), (char * )GETFUNCTION, (char *) GETFILE);
    ERROR_CODES_STACK ch5 =  StackDestructor(NULL);
    fprintf(log, "Stack Push result:        %s\n", ERRORS[ch1].error_message);
    fprintf(log, "Stack Pop result:         %s\n", ERRORS[ch2].error_message);
    fprintf(log, "Stack Copy result:        %s\n", ERRORS[ch3].error_message);
    fprintf(log, "Stack Constructor result: %s\n", ERRORS[ch4].error_message);
    fprintf(log, "Stack Destructor result:  %s\n", ERRORS[ch5].error_message);
    return allright_stack;
}


ERROR_CODES_STACK StackTestGuards(FILE * log) {
    stack test = {};
    STACK_CONSTRUCTOR(&test);
    StackPush(&test, 1);
    test.vanguard = VANGUARD;
    ERROR_CODES_STACK ch1 = StackPush(&test, 2);
    test.vanguard = VANGUARD ^ (uintptr_t)&test;
    test.rearguard = REARGUARD;
    ERROR_CODES_STACK ch2 = StackPush(&test, 2);
    fprintf(log, "Vanguard test result:     %s\n", ERRORS[ch1].error_message);
    fprintf(log, "Rearguard test result:    %s\n", ERRORS[ch2].error_message);
    return allright_stack;
}
ERROR_CODES_STACK StackTestDataGuards(FILE * log) {
    stack test = {};
    STACK_CONSTRUCTOR(&test);
    StackPush(&test, 1);
    test.data[0] = 908;
    ERROR_CODES_STACK ch1 = StackPush(&test, 676);
    test.data[0] = ARR_VANGUARD;
    test.data[3] = 67;
    ERROR_CODES_STACK ch2 = StackPush(&test, 676);
    fprintf(log, "Arr Vanguard test result: %s\n", ERRORS[ch1].error_message);
    fprintf(log, "Arr Rearguard test result:%s\n", ERRORS[ch2].error_message);
    return allright_stack;
}
ERROR_CODES_STACK StackTestHashesTest(FILE * log) {
    stack test = {};
    STACK_CONSTRUCTOR(&test);
    StackPush(&test, 1);
    test.data[1] = 67;
    ERROR_CODES_STACK ch1 = StackPush(&test, 1);
    fprintf(log, "Data interruption test    %s\n", ERRORS[ch1].error_message);
    return allright_stack;
}
