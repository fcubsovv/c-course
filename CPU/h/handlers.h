#ifndef CPU_HANDLERS
#define CPU_HANDLERS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "../../stack/h/_STACK_.h"
#include "cpu.h"


struct CommandEntrails{
    STATES_CPU command_number;
    int command_type;
    long long arg;
};

STATES_CPU HandlePush               (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandlePop                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleAdd                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleSub                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleDiv                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleOut                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleHlt                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleIn                 (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleCall               (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleRet                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleDraw               (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleJumpIfGreater      (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleJumpGreaterOrEqual (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleJumpIfLess         (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleJumpIfLessOrEqual  (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleJump               (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandlePrintRam           (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleMul                (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleSqrt               (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleJumpIfEqual        (CommandEntrails command_entrails, cpu * CPU);
STATES_CPU HandleJumpIfNotEqual     (CommandEntrails command_entrails, cpu * CPU);


#endif
