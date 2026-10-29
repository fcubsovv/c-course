#include "../h/handlers.h"
#include "../h/raylib.h"
#include <stdlib.h>
#include <math.h>
#define LAST_8_BITS 0xFFu

STATES_CPU HandlePush(CommandEntrails command_entrails, struct cpu * CPU) {

    switch((int)command_entrails.command_type) {

        case no_argument:
            printf("command type %d\n", (int)command_entrails.command_type);
            printf("command type %d\n", command_entrails.command_type);
            printf("command arg %lg", command_entrails.arg);
            perror("nothing to push");
            return error_cpu;
        case int_argument:
            StackPush(&(CPU->MAIN_DATA), (double)command_entrails.arg);
            break;
        case reg_argument:
            switch((int)command_entrails.arg) {
            case 1: StackPush(&CPU->MAIN_DATA, CPU->ax); break;
            case 2: StackPush(&CPU->MAIN_DATA, CPU->bx); break;
            case 3: StackPush(&CPU->MAIN_DATA, CPU->cx); break;
            case 4: StackPush(&CPU->MAIN_DATA, CPU->dx); break;
            default: perror("no such register");
            }
            break;
        case ram_int_argument://[5]
            StackPush(&CPU->MAIN_DATA, CPU->RAM[(size_t)command_entrails.arg]);
            break;
        case ram_reg_argument://[AX]
            switch((int)command_entrails.arg) {
                case 1: StackPush(&CPU->MAIN_DATA, CPU->RAM[(size_t)CPU->ax]); break;
                case 2: StackPush(&CPU->MAIN_DATA, CPU->RAM[(size_t)CPU->bx]); break;
                case 3: StackPush(&CPU->MAIN_DATA, CPU->RAM[(size_t)CPU->cx]); break;
                case 4: StackPush(&CPU->MAIN_DATA, CPU->RAM[(size_t)CPU->dx]); break;
                default: perror("no such register");
            }
            break;
        default:
            perror("nothing to push");
            return error_cpu;
            break;
    }

    return read_command_cpu;
}

STATES_CPU HandlePop(CommandEntrails command_entrails, cpu * CPU) {
    double popped_val = 0;
    switch((int)command_entrails.command_type) {
            case reg_argument:
                StackPop(&(CPU->MAIN_DATA), &popped_val);
                switch((int)command_entrails.arg) {
                    case 1: CPU->ax = popped_val; break;
                    case 2: CPU->bx = popped_val; break;
                    case 3: CPU->cx = popped_val; break;
                    case 4: CPU->dx = popped_val; break;
                };
                break;
            case ram_int_argument:
                StackPop(&(CPU->MAIN_DATA), &popped_val);
                (CPU->RAM)[(size_t)command_entrails.arg] = popped_val;
                break;
            case ram_reg_argument:
                StackPop(&(CPU->MAIN_DATA), &popped_val);
                switch((int)command_entrails.arg) {
                    case 1: CPU->RAM[(size_t)CPU->ax] = popped_val; break;
                    case 2: CPU->RAM[(size_t)CPU->bx] = popped_val; break;
                    case 3: CPU->RAM[(size_t)CPU->cx] = popped_val; break;
                    case 4: CPU->RAM[(size_t)CPU->dx] = popped_val; break;
                };
                break;
            default:
                perror("nothing to push");
                return error_cpu;
                break;
        }
    return read_command_cpu;
}

int pop_b_and_a (cpu * CPU, double * a, double * b) {
    StackPop(&CPU->MAIN_DATA, b);
    StackPop(&CPU->MAIN_DATA, a);
    return 1;
}

STATES_CPU HandleAdd(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    StackPush(&CPU->MAIN_DATA, a + b);
    return read_command_cpu;
}

STATES_CPU HandleSub(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    StackPush(&CPU->MAIN_DATA, a - b);
    return read_command_cpu;
}

STATES_CPU HandleDiv(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    StackPush(&CPU->MAIN_DATA, a / b);
    return read_command_cpu;
}

STATES_CPU HandleOut(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    printf("ELEMENT: %lg\n", b);
    return read_command_cpu;
}

STATES_CPU HandleHlt(CommandEntrails command_entrails, cpu * CPU) {
    return run_hlt_cpu;
}

STATES_CPU HandleIn(CommandEntrails command_entrails, cpu * CPU) {
    double a = 0;
    puts("insert element");
    scanf("%lg", &a);
    StackPush(&CPU->MAIN_DATA, a);
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

Color GetPixelColor(uint64_t pixel) {
    Color pixel_color = {
        (uint8_t)((((uint32_t)pixel) >> 24) & LAST_8_BITS),
        (uint8_t)((((uint32_t)pixel) >> 16) & LAST_8_BITS),
        (uint8_t)((((uint32_t)pixel) >> 8) & LAST_8_BITS),
        (uint8_t)(((uint32_t)pixel) & LAST_8_BITS)
    };
    return pixel_color;
}

STATES_CPU HandleDraw(CommandEntrails command_entrails, cpu * CPU) {
    size_t arr_length  = sizeof(CPU->RAM)/sizeof(CPU->RAM[0]);
    int side = (int)sqrt(arr_length);
    int pixel_scale = 20;
    int window_width = side * pixel_scale;
    int window_height = side * pixel_scale;
    InitWindow(window_width, window_height, "pick me");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int y = 0; y < side; y++) {
            for (int x = 0; x < side; x++) {
                int index = y * side + x;
                uint64_t element = (uint64_t)CPU->RAM[index];

                Color color = GetPixelColor(element);

                DrawRectangle(
                    x * pixel_scale,
                    y * pixel_scale,
                    pixel_scale,
                    pixel_scale,
                    color
                );
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return read_command_cpu;
}

STATES_CPU HandleJump(CommandEntrails command_entrails, cpu * CPU) {
    switch((int)command_entrails.command_type) {
        case int_argument:
            CPU->IP = (int)command_entrails.arg;
            break;
        case reg_argument:
            switch((int)command_entrails.arg) {
                case 1: CPU->IP = CPU->ax; break;
                case 2: CPU->IP = CPU->bx; break;
                case 3: CPU->IP = CPU->cx; break;
                case 4: CPU->IP = CPU->dx; break;
            }
            break;
        case ram_int_argument:
            CPU->IP = (CPU->RAM)[(size_t)command_entrails.arg];
            break;
        case ram_reg_argument:
            switch((int)command_entrails.arg) {
                case 1: CPU->IP = (CPU->RAM)[(size_t)CPU->ax]; break;
                case 2: CPU->IP = (CPU->RAM)[(size_t)CPU->ax]; break;
                case 3: CPU->IP = (CPU->RAM)[(size_t)CPU->ax]; break;
                case 4: CPU->IP = (CPU->RAM)[(size_t)CPU->ax]; break;
            }
            break;
        default:
            printf("unreachable argument in jump line %d\n", CPU->IP);
            return error_cpu;
            break;
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpIfGreater(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    if (a > b) {
        HandleJump(command_entrails, CPU);
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpGreaterOrEqual(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    if (a >= b) {
        HandleJump(command_entrails, CPU);
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpIfLess(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    if (a < b) {
        HandleJump(command_entrails, CPU);
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpIfLessOrEqual(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    if (a <= b) {
        HandleJump(command_entrails, CPU);
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpIfEqual (CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    if (a == b) {
        HandleJump(command_entrails, CPU);
    }
    return read_command_cpu;
}

STATES_CPU HandleJumpIfNotEqual (CommandEntrails command_entrails, cpu * CPU)  {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    if (a != b) {
        HandleJump(command_entrails, CPU);
    }
    return read_command_cpu;
}

STATES_CPU HandlePrintRam(CommandEntrails command_entrails, cpu * CPU) {//TODO проверки и остальные какашки
    for (size_t i = 0; i < sizeof(CPU->RAM)/sizeof(double); i++) {
        printf("%lg ", CPU->RAM[i]);
    }
    printf("\n");
    return read_command_cpu;
}


STATES_CPU HandleMul(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN, a = NAN;
    pop_b_and_a(CPU, &a, &b);
    StackPush(&CPU->MAIN_DATA, a*b);
    return read_command_cpu;
}

STATES_CPU HandleSqrt(CommandEntrails command_entrails, cpu * CPU) {
    double b = NAN;
    StackPop(&CPU->MAIN_DATA, &b);
    StackPush(&CPU->MAIN_DATA, sqrt(b));
    return read_command_cpu;
}
