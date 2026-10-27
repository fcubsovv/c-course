#ifndef COMMANDS
#define COMMANDS
#include "handlers.h"

struct cpu_command {
    const char * command_name;
    STATES_CPU   command_number;
    STATES_CPU (*handler)(CommandEntrails, cpu *);
};

const cpu_command COMMANDS_CPU[] = {
    {"PUSH", run_push_cpu,      HandlePush},
    {"ADD",  run_add_cpu,       HandleAdd},
    {"SUB",  run_sub_cpu,       HandleSub},
    {"DIV",  run_div_cpu,       HandleDiv},
    {"OUT",  run_out_cpu,       HandleOut},
    {"HLT",  run_hlt_cpu,       HandleHlt},
    {"IN",   run_in_cpu,        HandleIn},
    {"CALL", run_call_cpu,      HandleCall},
    {"RET",  run_ret_cpu,       HandleRet},
    {"POP",  run_pop_cpu,       HandlePop},
    {"DRAW", run_draw_cpu,      HandleDraw},
    {"JG",   run_jg_cpu,        HandleJumpIfGreater},
    {"JGE",  run_jge_cpu,       HandleJumpGreaterOrEqual},
    {"JL",   run_jl_cpu,        HandleJumpIfLess},
    {"JLE",  run_jle_cpu,       HandleJumpIfLessOrEqual},
    {"PR",   run_pr_ram_cpu,    HandlePrintRam},
    {"JP",   run_jp_cpu,        HandleJump},
    //{"XXX",  read_command_cpu,  HandleReadCommandSpu}
};

;

#endif
