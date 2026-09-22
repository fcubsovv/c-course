#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../stringsh/user_string.cpp"
#include "../sorting/user_qsort.cpp"

#define PRINT_LINE n_fputs("_______________________________________________\n", answer_file);

struct line {
    char * str;
    size_t length;
};

int WhiteArrayToFile(void * array, )

int n_fputs(const char *str, FILE *stream) {
    while (*str != '\n' && *str != '\0') {
        if (fputc(*str, stream) == EOF) {
            return EOF;
        }
        str++;
    }
    if (*str == '\n') {
        if (fputc('\n', stream) == EOF) {
            return EOF;
        }
    }
    return 0;
}

int CompareLinesAscending(const void * str1_struct, const void * str2_struct) {
    if (!str1_struct) {
        fprintf(stderr, "error in CompareLinesAscending, no str1_struct");
    }
    if (!str2_struct) {
        fprintf(stderr, "error in CompareLinesAscending, no str2_struct");
    }
    const char *s1 = ((const line *)str1_struct) -> str;
    const char *s2 = ((const line *)str2_struct) -> str;
    int len_1 = ((line*)str1_struct)->length;
    int len_2 = ((line*)str2_struct)->length;
    int i = 0;
    int j = 0;
    while (1) {
        while (i < len_1 && s1[i] != '\n' && s1[i]!= '\0' && !isalpha((unsigned char)s1[i])) {
            i++;
        }
        while (j < len_2 && s2[j] != '\n' && s2[j]!='\0'&& !isalpha((unsigned char)s2[j])) {
            j++;
        }
        if ((i >= len_1 || s1[i] == '\0' || s1[i] == '\n') && (j >= len_2 || s2[j] == '\0' || s2[j] == '\n')) {
            return 0;
        }
        if (s1[i] == '\0' || s1[i] == '\n' || i >= len_1) {
            return -1;
        }
        if (s2[j] == '\0' || s2[j] == '\n' || j >= len_2) {
            return 1;
        }
        if (tolower((unsigned char)s1[i]) != tolower((unsigned char)s2[j])) {
            return tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[j]);
        }
        i++;
        j++;
    }
    return tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[j]);
}

int CompareLinesDescending(const void * str1_struct, const void * str2_struct) {
    if (!str1_struct) {
        fprintf(stderr, "error in CompareLinesDescending, no str1_struct");
    }
    if (!str2_struct) {
        fprintf(stderr, "error in CompareLinesDescending, no str2_struct");
    }
    const char *s1 = ((const line *)str1_struct) -> str;
    const char *s2 = ((const line *)str2_struct) -> str;
    int i = ((line*)str1_struct)->length - 1;
    int j = ((line*)str2_struct)->length - 1;
    while (1) {
        while (i >= 0 && !isalpha((unsigned char)s1[i])) {
            i--;
        }
        while (j >= 0 && !isalpha((unsigned char)s2[j])) {
            j--;
        }
        if(i < 0 && j < 0) {
            return 0;
        }
        if (i < 0) return  1;
        if (j < 0) return -1;
        if (tolower((unsigned char)tolower(s1[i])) != tolower((unsigned char)tolower(s2[j]))) {
            return  tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[j]);
        }
        i--;
        j--;
    }
    return tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[j]);
}

char * open_file(char * file_name);//how)

int main() {//big main
    int file = open("eugene.txt" , O_RDONLY, 0);
    if (file == -1) {
        fprintf(stderr, "cant open input file");
        return 0;
    }

    struct stat buff;
    fstat(file, &buff);
    size_t nitems = buff.st_size;
    char * text = (char *) calloc(nitems+1, sizeof(char));
    char * text_ptr = text;
    if (text == NULL) {
        puts("error in memory usage for text");
        return 0;
    }

    int read_result = read(file, text, nitems);
    if (read_result == -1 || read_result != nitems) {
        fprintf(stderr, "error in reading input file");
        return 0;
    }

    size_t lines_count = 0;
    size_t memory_tracker = 16;
    size_t previous_line_end = 0;
    line * lines_array = (line *)calloc(memory_tracker, sizeof(line));
    lines_array[lines_count++].str = &text[0];
    for (size_t i = 1; i < nitems; i++) {
        if (text[i] == '\n') {
            lines_array[lines_count-1].length = i-previous_line_end;
            if ((i+1) < nitems) {
                if (lines_count >= memory_tracker) {
                    memory_tracker*=2;
                    lines_array = (line*)realloc(lines_array, memory_tracker*(sizeof(line)));
                    if (lines_array == NULL) {
                        fprintf(stderr, "Error in memory usage, cannot expand lines_array");
                        return 0;
                    }
                }
                lines_array[lines_count++].str = &text[i+1];
                previous_line_end = i+1;
            }
        }
    }
    if (lines_count > 0) {
        lines_array[lines_count-1].length = nitems - previous_line_end;
    }

    int close_result = close(file);
    if (close_result != 0) {
        fprintf(stderr, "error in closing file occured");
    }

    FILE * answer_file = fopen("zheka1.txt", "w");//read buffer funciton
    qsort(lines_array, lines_count, sizeof(line), CompareLinesAscending);


    for(size_t i = 0; i < lines_count; i++) {
        n_fputs(lines_array[i].str, answer_file);
    }

    PRINT_LINE

    user_Hoare_qsort(lines_array, lines_count, sizeof(line), CompareLinesDescending);

    for(size_t i = 0; i < lines_count; i++) {
        n_fputs(lines_array[i].str, answer_file);
    }

    PRINT_LINE

    for(size_t i = 0; i < lines_count; i++) {
        n_fputs(text, answer_file);
        text = strchr(text, '\n');
        if (text == NULL) {
            break;
        } else {
            text++;
        }

    }


    fclose(answer_file);
    puts("success");
    free(text_ptr);
    free(lines_array);
    return EXIT_SUCCESS;
}
