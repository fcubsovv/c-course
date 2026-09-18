#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "../stringsh/user_string.cpp"
#include "../sorting/user_qsort.cpp"

#define PRINT_LINE puts("_______________________________________________");
//TODO форматирование текста на питоне
//DONE чтение - единым буффером
//DONE чтение гетлайном
//DONE компаратор для строк
//TODO comparators in a specific file
//DONE my_comp for lines
//DONE mycomp descending

int CompareLinesAscending(const void * str1, const void * str2) {
    assert(str1);
    assert(str2);
    const char *s1 = *(const char **)str1;
    const char *s2 = *(const char **)str2;
    int i = 0;
    int j = 0;
    while (1) {
        while (s1[i] != '\n' && s1[i]!='\0'&& !isalpha((unsigned char)s1[i])) {
            i++;
        }
        while (s2[j] != '\n' && s2[j]!='\0'&& !isalpha((unsigned char)s2[j])) {
            j++;
        }

        if ((s1[i] == '\0' || s1[i] == '\n') && (s2[j] == '\0' || s2[j] == '\n')) {
            return 0;
        }
        if (s1[i] == '\0' || s1[i] == '\n') {
            return -1;
        }
        if (s2[j] == '\0' || s2[j] == '\n') {
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

int CompareLinesDescending(const void * str1, const void * str2) {
    assert(str1);
    assert(str2);
    const char *s1 = * (const char * *)str1;
    const char *s2 = * (const char * *)str2;
    int i = strlen(s1) - 1;
    int j = strlen(s2) - 1;
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

int CompareLinesByPointers (const void * str1, const void * str2) {
    return str2 > str1;
}


int main() {
    char * line = NULL;
    const size_t number_of_lines = 7000;
    size_t len = 0;
    ssize_t read = 0;
    FILE * file = fopen("zheka_english.txt", "rb");
    assert(file);
    fseek(file, 0L, SEEK_END);
    size_t nitems = ftell(file);
    char * text = (char *) calloc(nitems+1, sizeof(char));
    fseek(file, 0L, SEEK_SET);
    fread(text, sizeof(char), nitems, file);
    char * * file_lines = (char * *)calloc(number_of_lines, sizeof(char *));
    size_t lines_count = 1;
    file_lines[0] = &text[0];
    for (size_t i = 1; i < nitems; i++) {
        if (text[i] == '\n') {
            text[i] = '\0';
            if ((i+1) < nitems) {
                file_lines[lines_count] = &text[i+1];
                lines_count++;
            }

        }
    }
    fclose(file);
    free(line);
    qsort(file_lines, lines_count, sizeof(char *), CompareLinesAscending);
    assert(file_lines);
    FILE * answer_file = fopen("zheka.txt", "w");
    assert(answer_file);
    for(size_t i = 0; i < lines_count; i++) {
        fputs(file_lines[i], answer_file);
        fputs("\n", answer_file);
    }
    fprintf(answer_file, "_______________________________________________\n");
    qsort(file_lines, lines_count, sizeof(char *), CompareLinesDescending);
    assert(file_lines);
    for(size_t i = 0; i < lines_count; i++) {
        fputs(file_lines[i], answer_file);
        fputs("\n", answer_file);
    }
    puts("finale");
    fprintf(answer_file, "_______________________________________________\n");
    for(size_t i = 0; i < lines_count; i++) {
        fputs(text, answer_file);
        fputs("\n", answer_file);
        text = strchr(text, 0);
        text++;
    }
    fclose(answer_file);
    return EXIT_SUCCESS;
}
