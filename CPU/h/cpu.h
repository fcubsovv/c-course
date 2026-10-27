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
    double RAM[100];//полный квадрат это не эстетика я хочу 2х на 3х так что должно делиться на 6
};

enum STATES_CPU {
    read_command_cpu=0,
    run_push_cpu    =1,//+
    run_add_cpu     =2,//+
    run_sub_cpu     =3,//+
    run_div_cpu     =4,//+
    run_out_cpu     =5,//+
    run_hlt_cpu     =6,//+
    run_in_cpu      =7,//+
    run_call_cpu    =8,//дописочка
    run_ret_cpu     =9,//+
    run_pop_cpu     =10,//+
    run_draw_cpu    =11,//
    run_jg_cpu      =12,//+
    run_jge_cpu     =13,//+
    run_jl_cpu      =14,//+
    run_jle_cpu     =15,//+
    error_cpu       =-1,
};


#endif
