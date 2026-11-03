#include "../h/commands.h"
// SEE ../h/commands.h

STATES_CPU find_command_in_commands(char * command_name) {
    STATES_CPU command_number = error_finding_command;
    for (size_t i = 0; i <  sizeof(COMMANDS_CPU) / sizeof(COMMANDS_CPU[0]); i++) {
        if (strcmp(COMMANDS_CPU[i].command_name, command_name) == 0) {
            command_number = COMMANDS_CPU[i].command_number;
            break;
        }
    }
    return command_number;
}
