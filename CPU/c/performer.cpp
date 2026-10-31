#include "../h/performer.h"

const char * execute_file = "test-data/execute.bin";

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

int Perform(void) {

    FILE * file = fopen(execute_file, "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    size_t number_of_lines = size / sizeof(CommandEntrails);
    CommandEntrails * code = (CommandEntrails *)calloc(number_of_lines, sizeof(CommandEntrails));
    size_t got = fread(code, sizeof(CommandEntrails), number_of_lines, file);


    int num = 0, type = 0, consumed = 0;
    double val = 0;

    cpu CPU = {};
    CPU.IP = 0;
    STACK_CONSTRUCTOR(&CPU.MAIN_DATA);
    STACK_CONSTRUCTOR(&CPU.LABEL_STACK);

//*********************************************************************************************************************************************************************************************************************************

    STATES_CPU state = read_command_cpu;
    CommandEntrails current = {};
    int result = 0;

    while (state != run_hlt_cpu) {
    if (state == error_cpu) {
        fprintf(stderr, "error occurred!\n");
        result = 1;
        break;
    }
    if (CPU.IP >= number_of_lines) {
        fprintf(stderr, "IP out of range\n");
        result = 1;
        break;
    }
    current = code[CPU.IP];
    CPU.IP++;
    if (current.command_number < run_push_cpu || current.command_number > run_jp_cpu) {
        fprintf(stderr, "unknown command %d\n", (int)current.command_number);
        result = 1;
        break;
    }
    state = COMMANDS_CPU[current.command_number - 1].handler(current, &CPU);
    }

    if (result == 0) puts("performance finished successfully.");

//*********************************************************************************************************************************************************************************************************************************

    free(code);
   // free(read.buffer);
    return result;
}
