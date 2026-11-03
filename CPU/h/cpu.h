#ifndef CPU_H
#define CPU_H
#include "../../stack/h/_STACK_.h"

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

struct cpu {
//registers
    double registers[4];
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

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

enum REGISTERS {
    ax = 0,
    bx = 1,
    cx = 2,
    dx = 3,
};

enum STATES_CPU {
    allright        =0,
    read_command_cpu=0,
    run_push_cpu    =1,//++
    run_add_cpu     =2,//+
    run_sub_cpu     =3,//+
    run_div_cpu     =4,//+
    run_out_cpu     =5,//+
    run_hlt_cpu     =6,//+
    run_in_cpu      =7,//+
    run_call_cpu    =8,//+
    run_ret_cpu     =9,//+
    run_pop_cpu     =10,//++
    run_draw_cpu    =11,//
    run_jg_cpu      =12,//+
    run_jge_cpu     =13,//+
    run_jl_cpu      =14,//+
    run_jle_cpu     =15,//+
    run_pr_ram_cpu  =16,//+
    run_mul_cpu     =17,//+
    run_sqrt_cpu    =18,//+
    run_je_cpu      =19,//+
    run_jne_cpu     =20,//+
    run_jp_cpu      =21,//+
    error_cpu       =-1,
    error_finding_command = -2,
    error_opening_file    = -3,
    error_null_ptr        = -4,
    error_ip_out_of_range = -5,
    error_unknown_argument= -6,
    error_unknown_label   = -7,
    error_no_such_register= -8,
    error_pushing         = -9,
    error_popping         = -10,
    error_unreachable_jump= -11,
};

enum argument_types {
    unreachable_arg = -1,
    no_argument     = 0b0000,
    int_argument    = 0b0001,
    reg_argument    = 0b0010,
    ram_int_argument= 0b0101,
    ram_reg_argument= 0b0110,
};

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

#endif
