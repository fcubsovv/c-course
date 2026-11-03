#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "junky_generator.cpp"

#include "comparators.cpp"
#include "../global_utils/h/filework.h"

#include "../global_utils/colors.cpp"

#include "../sorting/user_qsort.cpp"

lines_array_struct FormLinesArray(buffer_struct read) {
    char unsigned * text =           read.buffer;
    size_t nitems =         read.nitems;
    size_t j = 0;
    size_t num_of_strings = 0;
    size_t previous_line_end = 0;
    for (int i = 0; i < nitems; i++) {
        if (text[i] == '\n') {
            num_of_strings++;
        }
    }
    line_struct * lines_array = (line_struct *)calloc(num_of_strings, sizeof(line_struct));
    lines_array[j].str = &text[0];
    j++;
    for (size_t i = 1; i < nitems; i++) {
        if (text[i] == '\n') {
            lines_array[j-1].length = i-previous_line_end;
            if (i+1 < nitems) {
                lines_array[j].str = &text[i+1];
                lines_array[j].position = j;
                j++;
                previous_line_end = i+1;
            }
        } else if (i == nitems) {
            lines_array[j-1].length = i-previous_line_end + 1;
        }
    }
    return {
        lines_array,
        j,
    };

}

int WriteArrayToFile(line_struct * array, size_t number_of_elements, FILE * answer_file, int puts(const unsigned char *, FILE *)) {
    int result_of_puts_func = 0;
    for(size_t i = 0; i < number_of_elements; i++) {
            result_of_puts_func = puts(array[i].str, answer_file);
            if (result_of_puts_func == EOF ) {
                perror("error in WriteArrayToFile, cannot write...");
            }
        }
    puts((unsigned char *)"__________________________________________________\n", answer_file);
    return 0;
}

struct mode_struct {
    const char * mode_name;
    int (*comporator)(const void *, const void *);
};

const mode_struct modes[] = {
    {"acc", CompareLinesAscending},
    {"decc", CompareLinesDescending},
    {"straight", CompareByPosition},
    {"rhyme", CompareLastThreeSymbols},
};

int RunCommand (const char * mode, line_struct * lines_array, size_t lines_count, FILE * answer_file, const char * lang) {
    int modecode = -1;
    size_t arrsize = sizeof(modes)/sizeof(mode_struct);
    for (size_t i = 0; i < arrsize ; i++) {
        if (strcmp(mode, modes[i].mode_name) == 0) {
            modecode = (int)i;
        }
    }
    if (modecode == -1) {
        return 0;
    }
    if (modecode == 3) {
        size_t generated_count = 1 * 14;
        line_struct * verse = GenerateSomeJunk(lines_array, lines_count, 1);
        WriteArrayToFile( verse, generated_count, answer_file, n_fputs);
        return 1;
    }
    qsort(            lines_array, lines_count, sizeof(line_struct), modes[modecode].comporator);
    WriteArrayToFile( lines_array, lines_count, answer_file, n_fputs);
    return 1;
}

int main(const int argc, const char * args[]) {

    const char * file = args[1];
    const char * lang = args[2];
    size_t start = 2;

    if (strcmp(lang, "--ru") == 0 ){
        start++;
        setlocale(LC_CTYPE, "ru_RU.CP1251");
    }

    buffer_struct read = ReadFromFileToBuffer(file);
    if (read.buffer == NULL || read.nitems == 0) {
        perror("Nothing to read, ReadFromFile returned nothing");
        return 0;
    }

    lines_array_struct formed_array =   FormLinesArray(read);
    line_struct * lines_array =         formed_array.lines;
    size_t lines_count =                formed_array.lines_count;

    FILE * answer_file = fopen("output_file.txt", "w");
    if (   answer_file == NULL) {
        perror("error in opening answer file occured");
    }

    for (size_t i = start; i < argc; i++) {
            int res = RunCommand(args[i], lines_array, lines_count, answer_file, lang);
            if (res == 0) {
                perror("No such mode!");
                return 0;
        }
    }
    int close_file_result = fclose(answer_file);
    if (close_file_result != 0) {
        perror("Cannot close answer file");
        return 0;
    }

    free(lines_array);
    colorPrint("SUCCESS", GRN);
    return EXIT_SUCCESS;

}
