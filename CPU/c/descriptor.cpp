#include "../h/descriptor.h"
#include <stdio.h>
//DONE struct for commands
//DONE commands array
//DONE from lines to int commands and to file
//TODO отрефакторить эту буквально навозную кучу, a именно
    //TODO включение битков тоже для простых случаев
    //TODO раздбить на подфункции
    //TODO мб отдельная функция для включения битков
//TODO function for separating buffer to lines in filesdfjkdj lib!
//TODO function search in array for global utils lib
//DONE ram [%31[^]]]
//TODO сортировка между проходами


struct label_entrails {
    char labe_name[32];
    int label_address;
};


int ReadLinesFromBuffer(buffer_struct buffer) {
    int command_count = 0;
    //первый проход
    label_entrails * label_arr = (label_entrails*)calloc(32, sizeof(label_entrails));
    size_t label_arr_ptr = 0;
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
        while (current_idx < buffer.nitems && buffer.buffer[current_idx] != '\n' && line_len < sizeof(line) - 1) {
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
        int is_label = 0;
        char label[32] = {};
        if(sscanf(line, "%31s", command) <= 0) {
            continue;
        }
        sscanf(line, "%31[^: ]: %n", label, &is_label);
        if (is_label > 0) {
            // add rashirenie massiva labels using realloc! ili pohui
            label_arr[label_arr_ptr].label_address = command_count;
            strcpy(label_arr[label_arr_ptr].labe_name, label);
            label_arr_ptr++;
            continue;
        }
        command_count++;
    }
    //второй проход
    current_idx = 0;
    line_no = 0;
    while (current_idx < buffer.nitems) {
        //TODO sdelat ondelnuy def read_line, вынести мб в отдельную функцию просто разбиение этой срани на строки? и итерирывать по строгам , но вообще есть проблема с этим, а нет какая пробоема у меня первый проход просто формирует массив меток а второй прото его пропускает заебись так и сделаю
        char line[128] = {};
        size_t line_len = 0;
        while (current_idx < buffer.nitems && buffer.buffer[current_idx] != '\n' && line_len < sizeof(line) - 1) {
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
    //


        char command[32] = {};
        char args[32] = {};
        int is_label = 0;
        sscanf(line, "%31[^: ]: %n", command, &is_label);
        if (is_label > 0) {//if label than pohui on label
            continue;
        }

        int res = sscanf(line, "%31s %31s", command, args);
        if (res <= 0) continue;// if nothing pohui next line

        int command_number = -1;
        int command_type = 0;
        int intarg = 0;

        for (size_t i = 0; i <  sizeof(COMMANDS_CPU) / sizeof(COMMANDS_CPU[0]); i++) {
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
            int is_label = 0;
            int is_work_wth_ram = 0;
            char label[32] = {};
            char inner_arg[32] = {};
            sscanf(args, "%31[^ ] %n", label, &is_label);
            sscanf(args, "[%31[^]]] %n", inner_arg, &is_work_wth_ram);
            if (is_work_wth_ram > 0) {
                command_type |= (1 << 2);//врубаю третий биток
                if (sscanf(inner_arg, "%lf", &intarg) == 1) {
                    command_type |= (1 << 0);//включены первый и третий битки
                }
                else if (strcmp(inner_arg, "AX") == 0) { command_type |= (1 << 1); intarg = 1; }//включены второй и третий битки
                else if (strcmp(inner_arg, "BX") == 0) { command_type |= (1 << 1); intarg = 2; }
                else if (strcmp(inner_arg, "CX") == 0) { command_type |= (1 << 1); intarg = 3; }
                else if (strcmp(inner_arg, "DX") == 0) { command_type |= (1 << 1); intarg = 4; }

                fprintf(file, "%d %d %d\n", command_number, command_type, intarg);
                continue;
            }

            if (sscanf(args, "%lf", &intarg) == 1) {
                command_type = 1;
            }

            else if (strcmp(args, "AX") == 0) { command_type = 2; intarg = 1; }
            else if (strcmp(args, "BX") == 0) { command_type = 2; intarg = 2; }
            else if (strcmp(args, "CX") == 0) { command_type = 2; intarg = 3; }
            else if (strcmp(args, "DX") == 0) { command_type = 2; intarg = 4; }

            else if(is_label > 0) {
                for (size_t i = 0; i < label_arr_ptr; i++) {
                    if(strcmp(label_arr[i].labe_name, label) == 0) {
                        intarg = label_arr[i].label_address;
                        command_type = 1;
                    }
                }
            }
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


