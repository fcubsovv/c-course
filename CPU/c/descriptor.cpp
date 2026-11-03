#include "../h/descriptor.h"


struct label_entrails {
    char labe_name[64];
    int label_address;
};

static int get_command_line (size_t * current_idx, buffer_struct buffer, char * line, size_t line_size, size_t * line_len);
static int find_label_in_label_arr (label_entrails * label_arr, size_t label_arr_size, char * label_name, long long * intarg, int * command_type) ;

static int HandleExistingArgument (int * command_type, long long * intarg, char * args, int command_number, label_entrails * label_arr, size_t label_arr_ptr, int line_no);
static int FirstRun(size_t * command_count, buffer_struct buffer, label_entrails * label_arr, size_t * label_arr_ptr);

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

static int get_command_line (size_t * current_idx, buffer_struct buffer, char * line, size_t line_size, size_t * line_len) {
    while (*current_idx < buffer.nitems && buffer.buffer[*current_idx] != '\n' && *line_len < line_size - 1) {
        line[*line_len] = (char)buffer.buffer[*current_idx];
        (*line_len)++;
        (*current_idx)++;
    }
    if (*current_idx < buffer.nitems && buffer.buffer[*current_idx] == '\n') {
        (*current_idx) = (*current_idx) + 1;
    }
    line[*line_len] = '\0';
    return 0;
}

static int find_label_in_label_arr (label_entrails * label_arr, size_t label_arr_size, char * label_name, long long * intarg, int * command_type)  {
    for (size_t i = 0; i < label_arr_size; i++) {
        if(strcmp(label_arr[i].labe_name, label_name) == 0) {
            (*intarg) = label_arr[i].label_address;
            *command_type = 1;
            return 1;
        }
    }
    return -1;
}

static int HandleExistingArgument (int * command_type, long long * intarg, char * args, int command_number, label_entrails * label_arr, size_t label_arr_ptr, int line_no) {
    int is_label = 0;
    int is_work_wth_ram = 0;
    char label[64] = {};
    char inner_arg[64] = {};
    sscanf(args, " %31[^ ] %n", label, &is_label);
    sscanf(args, "[%31[^]]] %n", inner_arg, &is_work_wth_ram);
    if (is_work_wth_ram > 0) {
        *command_type |= (1 << 2);
        if (sscanf(inner_arg, "%lld", &*intarg) == 1) {
            *command_type |= (1 << 0);
        }
        else if (strcmp(inner_arg, "AX") == 0) { *command_type |= (1 << 1); *intarg = 1; }
        else if (strcmp(inner_arg, "BX") == 0) { *command_type |= (1 << 1); *intarg = 2; }
        else if (strcmp(inner_arg, "CX") == 0) { *command_type |= (1 << 1); *intarg = 3; }
        else if (strcmp(inner_arg, "DX") == 0) { *command_type |= (1 << 1); *intarg = 4; }
        return 1;
    }

    if (sscanf(args, "%lld", intarg) == 1) {
        *command_type = 1;
    }

    else if (strcmp(args, "AX") == 0) { *command_type = 2; *intarg = 1; }
    else if (strcmp(args, "BX") == 0) { *command_type = 2; *intarg = 2; }
    else if (strcmp(args, "CX") == 0) { *command_type = 2; *intarg = 3; }
    else if (strcmp(args, "DX") == 0) { *command_type = 2; *intarg = 4; }

    else if(is_label > 0) {
        if(find_label_in_label_arr(label_arr, label_arr_ptr, label, intarg, command_type) == -1) {
            printf("error label in line %d", line_no);
            return -1;
        };
    }
    else {
        printf("error unknown argument in line %d", line_no);
        return -1;
    }
    return 1;
}

static int FirstRun(size_t * command_count, buffer_struct buffer, label_entrails * label_arr, size_t * label_arr_ptr) {
    size_t current_idx = 0;
    int line_no = 0;
    while (current_idx < buffer.nitems) {

    char line[256] = {};
    size_t line_len = 0;
    get_command_line(&current_idx, buffer, line, sizeof(line), &line_len);

    line_no++;

    if (line_len == 0) {
        continue;
    }

    char command[64] = {};
    char args[64] = {};
    int is_label = 0;
    char label[64] = {};
    if(sscanf(line, "%31s", command) <= 0) {
        continue;
    }
    sscanf(line, " %31[^: ]: %n", label, &is_label);
    if (is_label > 0) {
        // add rashirenie massiva labels using realloc! ili pohui
        label_arr[*label_arr_ptr].label_address = *command_count;
        strcpy(label_arr[*label_arr_ptr].labe_name, label);
        (*label_arr_ptr)++;
        continue;
    }
    (*command_count)++;
    }
    return 0;
}

static int ReadLinesFromBuffer(buffer_struct buffer) {
    size_t command_count = 0;

    label_entrails * label_arr = (label_entrails*)calloc(64, sizeof(label_entrails));
    size_t label_arr_ptr = 0;

    FILE * file = fopen(decrypted_file, "wb"); //
    if (!file) {
        perror("error opening file");
        return -1;
    }
    //первый проход
    int result = 0;
    int line_no = 0;
    FirstRun(&command_count, buffer, label_arr, &label_arr_ptr);

    //второй проход
    size_t current_idx = 0;
    line_no = 0;
    while (current_idx < buffer.nitems) {
        char line[256] = {};
        size_t line_len = 0;
        get_command_line(&current_idx, buffer, line, sizeof(line), &line_len);
        line_no++;
        if (line_len == 0) continue;

        char command[64] = {};
        char args[64] = {};
        int is_label = 0;


        // char first_char = '\0';
        // int check = sscanf(line, " %c", &first_char);
        // if (check <= 0 || first_char == ';') continue;
        char * semi = strchr(line, ';');
        if (semi) *semi = '\0';
        if (line[strspn(line, " \t\r")] == '\0') continue;
        sscanf(line, " %31[^: ]: %n", command, &is_label);
        if (is_label > 0) continue;

        int res = sscanf(line, " %31s %63s", command, args);
        if (res <= 0) return 0;

        STATES_CPU command_number = find_command_in_commands(command);
        int command_type = 0;
        long long intarg = 0;

        if (command_number == -1) {
            printf("line %d: unavaliable command'%s'\n",  line_no, command);
            result = -1;
            break;
        }

        if (res == 2) {
            int res = HandleExistingArgument(&command_type, &intarg, args, command_number, label_arr, label_arr_ptr, line_no);
            if (res == 1) {
                CommandEntrails com = {command_number, command_type, intarg};
                fwrite(&com, sizeof(CommandEntrails), 1, file);
                continue;
            } else if (res == -1) {
                return -1;
            }
        } else {
            command_type = 0;
            intarg = 0;
        }
        CommandEntrails com = {command_number, command_type, intarg};
        fwrite(&com, sizeof(CommandEntrails), 1, file);
    }
    fclose(file);
    return result;
}

//_________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________


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


