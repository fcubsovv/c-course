#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "../stringsh/user_string.cpp"
#include "../sorting/user_qsort.cpp"

#define PRINT_LINE puts("_______________________________________________");
//TODO форматирование текста на питоне
//TODO чтение - единым буффером
//DONE чтение гетлайном
//DONE компаратор для строк
//TODO sorting by pointer value
//TODO make asc/desc directions same func??
//TODO comparators in a specific file
//DONE my_comp for lines
//TODO mycomp descending

int CompareLinesAscending(const void * str1, const void * str2) {
    puts("comare acc");
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
    puts("comare decc");
    assert(str1);
    assert(str2);
    const char *s1 = *(const char **)str1;
    const char *s2 = *(const char **)str2;
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
        if (i < 0) return 1;
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
    return str1 > str2;
}


int main() {
    char * line = NULL;
    const size_t number_of_lines = 7000;
    size_t len = 0;
    ssize_t read = 0;
    size_t j = 0;
    char * * lines = (char * *)calloc(number_of_lines, sizeof(char *));
    assert(lines);

    FILE * file = fopen("eugene.txt", "r");
    assert(file);
    while ((read = getline(&line, &len, file)) != -1) {
        lines[j] = strdup(line);
        assert(lines[j]);
        j++;
    }
    fclose(file);
    free(line);
    qsort(lines, j, sizeof(char *), CompareLinesAscending);
    assert(lines);
    FILE * answer_file = fopen("zheka.txt", "w");
    assert(answer_file);
    for(size_t i = 0; i < j; i++) {
        printf("%s", lines[i]);
        fputs(lines[i], answer_file);
    }
    fprintf(answer_file, "_______________________________________________\n");
    qsort(lines, j, sizeof(char *), CompareLinesDescending);
    assert(lines);
    for(size_t i = 0; i < j; i++) {
        printf("%s", lines[i]);
        fputs(lines[i], answer_file);
    }
    puts("finale");
    // fprintf(answer_file, "_______________________________________________\n");
    // qsort(lines, j, sizeof(char *), CompareLinesByPointers);
    // assert(lines);
    // for(size_t i = 0; i < j; i++) {
    //     fprintf(answer_file, lines[i]);
    // }
    fclose(answer_file);
    return EXIT_SUCCESS;
}
