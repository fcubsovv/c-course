#ifndef COMPARATORS
#define COMPARATORS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


struct line_struct {
    char * str;
    size_t length;
    size_t position;
};

int CompareLinesAscending(const void * str1_struct, const void * str2_struct) {
    if (!str1_struct) {
        perror("error in CompareLinesAscending, no str1_struct");
    }
    if (!str2_struct) {
        perror("error in CompareLinesAscending, no str2_struct");
    }
    const char *s1 = ((const line_struct *)str1_struct) -> str;
    const char *s2 = ((const line_struct *)str2_struct) -> str;
    int len_1 = ((line_struct*)str1_struct)->length;
    int len_2 = ((line_struct*)str2_struct)->length;
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
        perror("error in CompareLinesDescending, no str1_struct");
    }
    if (!str2_struct) {
        perror("error in CompareLinesDescending, no str2_struct");
    }
    const char *s1 = ((const line_struct *)str1_struct) -> str;
    const char *s2 = ((const line_struct *)str2_struct) -> str;
    int i = ((line_struct*)str1_struct)->length - 1;
    int j = ((line_struct*)str2_struct)->length - 1;
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

int CompareByPosition(const void * str1_struct, const void * str2_struct) {
    const size_t pos_1 = ((const line_struct *)str1_struct) -> position;
    const size_t pos_2 = ((const line_struct *)str2_struct) -> position;
    if (pos_1 < pos_2) {
        return -1;
    }
    if (pos_1 > pos_2) {
        return 1;
    }
    return 0;
}
#endif
