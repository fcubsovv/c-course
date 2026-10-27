#include "../h/handlers.h"

STATES_CPU HandlePush(CommandEntrails command_entrails, struct cpu * CPU) {
    if (command_entrails.command_type == 0) {
        perror("nothing to push");
        return error_cpu;
    }
    if (command_entrails.command_type == 1) {
        StackPush(&(CPU->MAIN_DATA), (double)command_entrails.arg);
    }
    if (command_entrails.command_type == 2) {
        switch((int)command_entrails.arg) {
            case 1:
                StackPush(&CPU->MAIN_DATA, CPU->ax);

                break;
            case 2:
                StackPush(&CPU->MAIN_DATA, CPU->bx);
                break;
            case 3:
                StackPush(&CPU->MAIN_DATA, CPU->cx);
                break;
            case 4:
                StackPush(&CPU->MAIN_DATA, CPU->dx);
                break;
            default:
                perror("no such register");
        }
    }
    return read_command_cpu;
}

STATES_CPU HandlePop(CommandEntrails command_entails, cpu * CPU) {
    if (command_entails.command_type == 2) {
        double popped_val = 0;
        StackPop(&(CPU->MAIN_DATA), &popped_val);
        switch((int)command_entails.arg) {
            case 1: CPU->ax = popped_val; break;
            case 2: CPU->bx = popped_val; break;
            case 3: CPU->cx = popped_val; break;
            case 4: CPU->dx = popped_val; break;
        }
    } else {
        return error_cpu;
    }
    return read_command_cpu;
}

STATES_CPU HandleAdd(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    double a;//init
    StackPop(&CPU->MAIN_DATA, &a);
    StackPush(&CPU->MAIN_DATA, a + b);
    return read_command_cpu;
}

STATES_CPU HandleSub(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    double a;//init
    StackPop(&CPU->MAIN_DATA, &a);
    StackPush(&CPU->MAIN_DATA, a - b);
    return read_command_cpu;
}
STATES_CPU HandleDiv(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    double a;//init
    StackPop(&CPU->MAIN_DATA, &a);
    StackPush(&CPU->MAIN_DATA, a / b);
    return read_command_cpu;
}

STATES_CPU HandleOut(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    StackPush(&CPU->MAIN_DATA, b);
    printf("ELEMENT: %lg\n", b);
    return read_command_cpu;
}

STATES_CPU HandleHlt(CommandEntrails command_entrails, cpu * CPU) {
    //хуй знает что тут писать еще тут надо дамп там майбэ
    return run_hlt_cpu;
}
STATES_CPU HandleIn(CommandEntrails command_entrails, cpu * CPU) {
    double love_me_suck_me = 0;
    puts("insert double");
    scanf("%lg", &love_me_suck_me);
    StackPush(&CPU->MAIN_DATA, love_me_suck_me);
    return read_command_cpu;
}

STATES_CPU HandleCall(CommandEntrails command_entrails, cpu * CPU) {
    StackPush(&CPU->LABEL_STACK, (double)CPU->IP);
    CPU->IP = (size_t)command_entrails.arg;
    return read_command_cpu;
}

STATES_CPU HandleRet(CommandEntrails command_entrails, cpu * CPU) {
    double new_ip = 0;
    StackPop(&CPU->LABEL_STACK, &new_ip);
    CPU->IP = (int)new_ip;
    return read_command_cpu;
}

STATES_CPU HandleDraw(CommandEntrails command_entrails, cpu * CPU) {
    return read_command_cpu;
}

STATES_CPU HandleJump(CommandEntrails command_entrails, cpu * CPU) {
    if (command_entrails.command_type == 1) {
            CPU->IP = (int)command_entrails.arg;
        }
        else if (command_entrails.command_type == 2) {
        switch((int)command_entrails.arg) {
            case 1: CPU->IP = CPU->ax; break;
            case 2: CPU->IP = CPU->bx; break;
            case 3: CPU->IP = CPU->cx; break;
            case 4: CPU->IP = CPU->dx; break;
            }
        }
    return read_command_cpu;
}


STATES_CPU HandleJumpIfGreater(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    double a;//init
    StackPop(&CPU->MAIN_DATA, &a);
    if (a > b) {
        if (command_entrails.command_type == 1) {
            CPU->IP = (int)command_entrails.arg;
        }
        else if (command_entrails.command_type == 2) {
        switch((int)command_entrails.arg) {
            case 1: CPU->IP = CPU->ax; break;
            case 2: CPU->IP = CPU->bx; break;
            case 3: CPU->IP = CPU->cx; break;
            case 4: CPU->IP = CPU->dx; break;
            }
        }
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpGreaterOrEqual(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    double a;//init
    StackPop(&CPU->MAIN_DATA, &a);
    if (a >= b) {
        if (command_entrails.command_type == 1) {
            CPU->IP = (int)command_entrails.arg;
        }
        else if (command_entrails.command_type == 2) {
        switch((int)command_entrails.arg) {
            case 1: CPU->IP = CPU->ax; break;
            case 2: CPU->IP = CPU->bx; break;
            case 3: CPU->IP = CPU->cx; break;
            case 4: CPU->IP = CPU->dx; break;
            }
        }
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpIfLess(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    double a;//init
    StackPop(&CPU->MAIN_DATA, &a);
    if (a < b) {
        if (command_entrails.command_type == 1) {
            CPU->IP = (int)command_entrails.arg;
        }
        else if (command_entrails.command_type == 2) {
        switch((int)command_entrails.arg) {
            case 1: CPU->IP = CPU->ax; break;
            case 2: CPU->IP = CPU->bx; break;
            case 3: CPU->IP = CPU->cx; break;
            case 4: CPU->IP = CPU->dx; break;
            }
        }
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpIfLessOrEqual(CommandEntrails command_entrails, cpu * CPU) {
    double b;//init
    StackPop(&CPU->MAIN_DATA, &b);
    double a;//init
    StackPop(&CPU->MAIN_DATA, &a);
    if (a <= b) {
        if (command_entrails.command_type == 1) {
            CPU->IP = (int)command_entrails.arg;
        }
        else if (command_entrails.command_type == 2) {
        switch((int)command_entrails.arg) {
            case 1: CPU->IP = CPU->ax; break;
            case 2: CPU->IP = CPU->bx; break;
            case 3: CPU->IP = CPU->cx; break;
            case 4: CPU->IP = CPU->dx; break;
            }
        }
    }
    return read_command_cpu;
}

//
//
// HandlerOutput HandleReadCommandSpu(CommandEntrails command_entrails, cpu * CPU) {
//     if  (CPU.IP > instructions_size) {
//         return run_hlt_cpu;
//     }
//     CommandEntrails current = code[CPU.IP];
//     CPU.IP++;
//     return {current, current.command_number};
// }
