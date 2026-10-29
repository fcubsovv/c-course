#ifndef CPU_H
#define CPU_H
#include "../../stack/h/_STACK_.h"

struct cpu {
//registers
    double ax;
    double bx;
    double cx;
    double dx;
//main stack
    stack MAIN_DATA;
//label stack
    stack LABEL_STACK;
//ip - current line
    size_t IP;
    size_t instructions_size;
//ram = [-,-,-,-,-] len==100
    double RAM[2500];//полный квадрат это не эстетика я хочу 2х на 3х так что должно делиться на 6
};

enum STATES_CPU {
    read_command_cpu=0,
    run_push_cpu    =1,//++
    run_add_cpu     =2,//+
    run_sub_cpu     =3,//+
    run_div_cpu     =4,//+
    run_out_cpu     =5,//+
    run_hlt_cpu     =6,//+
    run_in_cpu      =7,//+//TODO написать тут что IN может быть с любыми аргументами при себе
    run_call_cpu    =8,//додристочка+
    run_ret_cpu     =9,//+
    run_pop_cpu     =10,//++
    run_draw_cpu    =11,//
    run_jg_cpu      =12,//+
    run_jge_cpu     =13,//+
    run_jl_cpu      =14,//+
    run_jle_cpu     =15,//+
    run_pr_ram_cpu  =16,//+
    run_mul_cpu     =17,//
    run_sqrt_cpu    =18,//
    run_jp_cpu      =19,//+
    error_cpu       =-1,
};

enum argument_types {
    no_argument     = 0b000,//0000
    int_argument    = 0b001,//0001
    reg_argument    = 0b100,//0010
    ram_int_argument= 0b101,
    ram_reg_argument= 0b110,
};

#endif
