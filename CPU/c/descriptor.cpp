#include "../h/descriptor.h"
#include <stdio.h>
//TODO struct for commands
//TODO commands array
//TODO from buffer to lines
//TODO from lines to int commands and to file
//TODO

int ReadLinesFromBuffer(buffer_struct buffer) {
    FILE * file = fopen(decrypted_file, "w"); //
    if (!file) {
        perror("error opening file");
        return -1;
    }
    int result = 0;
    int line_no = 0;
    size_t current_idx = 0;
    while (current_idx < buffer.nitems) {
        char line[128] = {};
        size_t line_len = 0;
        while (current_idx < buffer.nitems &&
               buffer.buffer[current_idx] != '\n' &&
               line_len < sizeof(line) - 1) {

            line[line_len] = (char)buffer.buffer[current_idx];
            line_len++;
            current_idx++;
        }
        if (current_idx < buffer.nitems && buffer.buffer[current_idx] == '\n') {
            current_idx++;
        }
        line[line_len] = '\0';
        line_no++;
        if (line_len == 0) {
            continue;
        }
        char command[32] = {};
        char args[32] = {};

        int res = sscanf(line, "%31s %31s", command, args);
        if (res <= 0) continue;

        int command_number = -1;
        int command_type = 0;
        int intarg = 0;
        for (size_t i = 0; i < sizeof(COMMANDS_CPU) / sizeof(COMMANDS_CPU[0]); i++) {
            if (strcmp(COMMANDS_CPU[i].command_name, command) == 0) {
                command_number = (int)COMMANDS_CPU[i].command_number;
                break;
            }
        }

        if (command_number == -1) {
            printf("line %d: unavaiable command'%s'\n",  line_no, command);
            result = -1;
            break;
        }

        if (res == 2) {
            if (sscanf(args, "%d", &intarg) == 1) {
                command_type = 1;
            }
            else if (strcmp(args, "AX") == 0) { command_type = 2; intarg = 1; }
            else if (strcmp(args, "BX") == 0) { command_type = 2; intarg = 2; }
            else if (strcmp(args, "CX") == 0) { command_type = 2; intarg = 3; }
            else if (strcmp(args, "DX") == 0) { command_type = 2; intarg = 4; }
            else {
                printf("error unknown argument in line %d", line_no);
                result = -1;
                break;
            }
        } else {
            command_type = 0;
            intarg = 0;
        }
        fprintf(file, "%d %d %d\n", command_number, command_type, intarg);
    }

    fclose(file);
    return result;
}

int Descript(void) {
    buffer_struct read = ReadFromFileToBuffer(crypted_file);
    if (read.buffer == NULL || read.nitems == 0) {
        printf("Nothing to read, ReadFromFile returned nothing");
        return 0;
    }
    int result = ReadLinesFromBuffer(read);
    free(read.buffer);
    if (result != 0) {
        fprintf(stderr, "description failed.\n");
        return 1;
    }
    puts("description finished successfully.");
    return 0;
}
