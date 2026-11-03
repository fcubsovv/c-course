#include "../h/performer.h"

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

STATES_CPU Perform(void) {

    FILE * file = fopen(execute_file, "rb");
    if (!file) {
        perror("fopen");
                ErrorPuts(error_opening_file, GETFILE_CPU(result), GETFUNCTION_CPU(), GETLINE_CPU());
        return error_opening_file;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    size_t number_of_lines = size / sizeof(CommandEntrails);
    CommandEntrails * code = (CommandEntrails *)calloc(number_of_lines, sizeof(CommandEntrails));
    size_t got = fread(code, sizeof(CommandEntrails), number_of_lines, file);


    int num = 0, type = 0;
    double val = 0;

    cpu CPU = {};
    CPU.IP = 0;
    STACK_CONSTRUCTOR(&CPU.MAIN_DATA);
    STACK_CONSTRUCTOR(&CPU.LABEL_STACK);

//*********************************************************************************************************************************************************************************************************************************

    STATES_CPU state = read_command_cpu;
    CommandEntrails current = {};
    STATES_CPU result = allright;

    while (state != run_hlt_cpu || current.command_number < run_push_cpu || current.command_number > run_jp_cpu) {
    if (state == error_cpu) {
        fprintf(stderr, "error occurred!\n");

        break;
    }
    if (CPU.IP >= number_of_lines) {
        state = error_ip_out_of_range;
        break;
    }

    current = code[CPU.IP];
    CPU.IP++;
    if (current.command_number < run_push_cpu || current.command_number > run_jp_cpu) {
        fprintf(stderr, "error happened in line %zu\n", CPU.IP);
        fprintf(stderr, "cpu STATE %d\n", state);
        break;
    }
    state = COMMANDS_CPU[current.command_number - 1].handler(current, &CPU);
    }

    if (state == run_hlt_cpu) {
        puts("performance finished successfully.");
    } else {
        ErrorPuts(state, GETFILE_CPU(result), GETFUNCTION_CPU(), GETLINE_CPU());
    }

//*********************************************************************************************************************************************************************************************************************************

    free(code);
    return state;
}
