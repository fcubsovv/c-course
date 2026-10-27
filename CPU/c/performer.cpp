#include "../h/performer.h"
//struct CommandArgs;

//bitfield
//кодировка в окумментации арма для кодировки команд что куда типо получается что надо команы кодирвать по номеру или как это работает
//26 ти биткое число
const char * execute_file = "test-data/execute.txt";


int Perform(void) {
    buffer_struct read = ReadFromFileToBuffer(execute_file);
    if (read.buffer == NULL || read.nitems == 0) {
        fprintf(stderr, "Nothing to read, ReadFromFile returned nothing\n");
        return 1;
    }

    size_t lines = count_lines_helper(read) + 1;
    CommandEntrails *code = (CommandEntrails *)calloc(lines, sizeof(CommandEntrails));
    if (code == NULL) {
        fprintf(stderr, "calloc failed\n");
        free(read.buffer);
        return 1;
    }

    // парсинг из буфера
    size_t code_size = 0;
    const char * p = (char *)read.buffer;
    int num = 0, type = 0, consumed = 0;
    double val = 0;
    while (code_size < lines &&
           sscanf(p, "%d %d %lf%n", &num, &type, &val, &consumed) == 3) {
        code[code_size].command_number = (STATES_CPU)num;
        code[code_size].command_type   = type;
        code[code_size].arg            = val;
        code_size++;
        p += consumed;
    }

    cpu CPU = {};
    CPU.IP = 0;
    STACK_CONSTRUCTOR(&CPU.MAIN_DATA);
    STACK_CONSTRUCTOR(&CPU.LABEL_STACK);

    STATES_CPU state = read_command_cpu;
    CommandEntrails current = {};
    int result = 0;

    while (state != run_hlt_cpu) {
    if (state == error_cpu) {
        fprintf(stderr, "error occurred!\n");
        result = 1;
        break;
    }

    if (CPU.IP >= code_size) {
        fprintf(stderr, "IP out of range\n");
        result = 1;
        break;
    }
    current = code[CPU.IP];
    CPU.IP++;

    if (current.command_number < run_push_cpu || current.command_number > run_jle_cpu) {
        fprintf(stderr, "unknown command %d\n", (int)current.command_number);
        result = 1;
        break;
    }
    state = COMMANDS_CPU[current.command_number - 1].handler(current, &CPU);
}
if (result == 0) puts("performance finished successfully.");

free(code);
free(read.buffer);
return result;
}
