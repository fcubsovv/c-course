#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
//define tools
//tools
//define tools
//define conditions
#define DEBUG//in maim??
//define modes file
#include "stack_utils.cpp"
#include "stack.cpp"

//check можно ли по этому указателю что то записать которая читает состояние памяти
//hash fucntion using for stack, for stack.data
//void*??
//unit tests
//hash function uint64_t hash(void *, sizeof()) link to source/docs rot 12 crc32 в операцию хэширования добавить адрес чтобы нельзя было тоже копировать
//capacity includes +2
//varname



int main (int args, const char * argv[]) {

    stack myFrstStack = {};

    int errorcode = 0;
    errorcode = StackConstructor(&myFrstStack, (char * )GETNAME(myFrstStack), (char * )GETFUNCTION, (char *) GETFILE);
    ERROR_CODES re = StackPush(&myFrstStack, 89.0);
    StackPush(&myFrstStack, 2);
    StackPush(&myFrstStack, 4);
    StackPush(&myFrstStack, 7);
    StackPush(&myFrstStack, 9);
    StackPop(&myFrstStack);
    puts("");
    stack mySecondStack = {};
    ERROR_CODES res = CopyStack(&myFrstStack, &mySecondStack, (char*)GETFUNCTION, (char *)GETFILE, (char *)GETNAME(mySecondStack));
    STACK_LOG(&myFrstStack);
    STACK_LOG(&mySecondStack);
    printf("%d",  res);
//------------null ptrs-------------
    StackPush(NULL, 2);
    StackPop(NULL);
    CopyStack(NULL, NULL, (char*)GETFUNCTION, (char *)GETFILE, (char *)GETNAME(NULL));
    StackConstructor(NULL, (char * )GETNAME(NULL), (char * )GETFUNCTION, (char *) GETFILE);
    StackDestructor(NULL);
//-----------data vanguards---------------
    myFrstStack.data[0] = 908;
    StackPush(&myFrstStack, 676);
    myFrstStack.data[0] = ARR_VANGUARD;
//-----------struct vanguards--------------
    myFrstStack.vanguard = VANGUARD;
    mySecondStack.rearguard = REARGUARD;
    StackPush(&mySecondStack, 676);
    StackPop(&myFrstStack);
    myFrstStack.vanguard = VANGUARD ^ (uintptr_t)&myFrstStack;
//------------data hash-------------------
    myFrstStack.data[1] = 67;
    StackPop(&myFrstStack);
    return 0;
}

