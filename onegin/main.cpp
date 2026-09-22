#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "comparators.cpp"

#include "../global_utils/user_string.cpp"
#include "../global_utils/colors.cpp"
#include "../global_utils/filework.cpp"
#include "../global_utils/log_utils.cpp"

#include "../sorting/user_qsort.cpp"


struct lines_array_struct {
    line_struct * lines;
    size_t lines_count;
};

lines_array_struct FormLinesArray(char * text, size_t nitems) {

    struct lines_array_struct answer = {
        NULL,
        NULL
    };

    size_t lines_count = 0;
    size_t memory_tracker = 8;
    size_t previous_line_end = 0;

    line_struct * lines_array = (line_struct *)calloc(memory_tracker, sizeof(line_struct));

    lines_array[lines_count].str = &text[0];
    lines_count++;
    for (size_t i = 1; i < nitems; i++) {
        if (text[i] == '\n') {

            lines_array[lines_count-1].length = i-previous_line_end;

            if ((i+1) < nitems) {

                if (lines_count >= memory_tracker) {

                    memory_tracker *= 2;
                    lines_array = (line_struct *)realloc(lines_array, memory_tracker*(sizeof(line_struct)));

                    if (lines_array == NULL) {
                        perror("Error in memory usage, cannot expand lines_array");
                        return answer;
                    }
                }

                lines_array[lines_count].str = &text[i+1];
                lines_array[lines_count].position = lines_count;
                lines_count++;
                previous_line_end = i+1;
            }
        }
    }

    answer = {
        lines_array,
        lines_count
    };

    return answer;
}

int WriteArrayToFile(line_struct * array, size_t number_of_elements, FILE * answer_file, int puts(const char *, FILE *)) {
    int result_of_puts_func = 0;
    for(size_t i = 0; i < number_of_elements; i++) {
            result_of_puts_func = puts(array[i].str, answer_file);
            if (result_of_puts_func == EOF ) {
                perror("error in WriteArrayToFile, cannot write...");
            }
        }
    PRINT_LINE
    return 0;
}

int main() {

    buffer_struct read =    ReadFromFileToBuffer("test_data/eugene.txt");
    char * text =           read.buffer;
    size_t nitems =         read.nitems;

    lines_array_struct formed_array =   FormLinesArray(text, nitems);
    line_struct * lines_array =         formed_array.lines;
    size_t lines_count =                formed_array.lines_count;

    FILE * answer_file = fopen("output_file.txt", "w");
    if (   answer_file == NULL) {
        perror("error in opening answer file occured, no such file");
    }

    qsort(            lines_array, lines_count, sizeof(line_struct), CompareLinesAscending);
    WriteArrayToFile( lines_array, lines_count, answer_file, n_fputs);

    user_Hoare_qsort( lines_array, lines_count, sizeof(line_struct), CompareLinesDescending);
    WriteArrayToFile( lines_array, lines_count, answer_file, n_fputs);

    user_Lamuto_qsort(lines_array, lines_count, sizeof(line_struct), CompareByPosition);
    WriteArrayToFile( lines_array, lines_count, answer_file, n_fputs);

    int close_file_result = fclose(answer_file);
    if (close_file_result != 0) {
        perror("Cannot close answer file");
        return 0;
    }

    free(lines_array);
    colorPrint("SUCCESS", GRN);
    return EXIT_SUCCESS;

}
