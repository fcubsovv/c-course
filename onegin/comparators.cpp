#ifndef COMPARATORS
#define COMPARATORS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


struct line_struct {
    unsigned char * str;
    size_t length;
    size_t position;
};


int isalpha_cp1251(unsigned char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 1;
    }
    if ((c >= 0xC0 && c <= 0xFF) || c == 0xA8 || c == 0xB8) {
        return 1;
    }
    return 0;
}

size_t skip_junk_symbols_acc(const unsigned char * s1, size_t len_1, size_t index) {
    while (index < len_1 && s1[index] != '\n' && s1[index]!= '\0' && !isalpha_cp1251((unsigned char)s1[index])) {
        index++;
    }
    return index;
}

size_t skip_junk_symbols_dec(const unsigned char * s1, ssize_t index) {
    while (index >= 0 && !isalpha_cp1251(s1[index])) {
        index--;
    }
    return index;
}

int CompareLinesAscending(const void * str1_struct, const void * str2_struct) {

    if (!str1_struct) {
        perror("error in CompareLinesAscending, no str1_struct");
    }
    if (!str2_struct) {
        perror("error in CompareLinesAscending, no str2_struct");
    }

    const unsigned char *s1 = ((const line_struct *)str1_struct) -> str;
    const unsigned char *s2 = ((const line_struct *)str2_struct) -> str;
    int len_1 = ((line_struct*)str1_struct)->length;
    int len_2 = ((line_struct*)str2_struct)->length;

    int i = 0;
    int j = 0;
    int difference = 0;
    while (1) {
        i = skip_junk_symbols_acc(s1, len_1, i);
        j = skip_junk_symbols_acc(s2, len_2, j);
        int i_ended = (i >= len_1 || s1[i] == '\0' || s1[i] == '\n') ;
        int j_ended = (j >= len_2 || s2[j] == '\0' || s2[j] == '\n');
        if (i_ended && j_ended) {
            return 0;
        }
        if (i_ended) {
            return -1;
        }
        if (j_ended) {
            return 1;
        }
        difference = tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[j]);
        if (difference != 0) {
            return difference;
        }
        i++;
        j++;
    }
    return difference;
}

int CompareLinesDescending(const void * str1_struct, const void * str2_struct) {
    if (!str1_struct) {
        perror("error in CompareLinesDescending, no str1_struct");
    }
    if (!str2_struct) {
        perror("error in CompareLinesDescending, no str2_struct");
    }
    const unsigned char *s1 = ((const line_struct *)str1_struct) -> str;
    const unsigned char *s2 = ((const line_struct *)str2_struct) -> str;
    ssize_t i = ((line_struct*)str1_struct)->length - 1;
    ssize_t j = ((line_struct*)str2_struct)->length - 1;
    int difference = 0;
    while (1) {

        i = skip_junk_symbols_dec(s1, i);
        j = skip_junk_symbols_dec(s2, j);

        int i_ended = i < 0;
        int j_ended = j < 0;

        if (i_ended && j_ended) {
            return 0;
        }
        if (i_ended) return  1;
        if (j_ended) return -1;

        difference = tolower((unsigned char)s1[i]) - tolower((unsigned char)s2[j]);
        if (difference != 0) {
            return  difference;
        }
        i--;
        j--;
    }
    return difference;
}

int CompareLastThreeSymbols(const void * str1_struct, const void * str2_struct) {
    if (!str1_struct) {
        perror("error in CompareLinesDescending, no str1_struct");
    }
    if (!str2_struct) {
        perror("error in CompareLinesDescending, no str2_struct");
    }
    const unsigned char *s1 = ((const line_struct *)str1_struct) -> str;
    const unsigned char *s2 = ((const line_struct *)str2_struct) -> str;
    ssize_t i = (ssize_t)(((const line_struct*)str1_struct)->length) - 1;
    ssize_t j = (ssize_t)(((const line_struct*)str2_struct)->length) - 1;
    int difference = 0;
    int N = 3;
    while (N > 0) {

        i = skip_junk_symbols_dec(s1, i);
        j = skip_junk_symbols_dec(s2, j);

        int i_ended = i < 0;
        int j_ended = j < 0;

        if (i_ended && j_ended) {
            return 0;
        }
        if (i_ended) return  -1;
        if (j_ended) return 1;

        difference = tolower(s1[i]) - tolower(s2[j]);
        if (difference != 0) {
            return  difference;
        }
        i--;
        j--;
        N--;
    }
    return difference;

}

int CompareByPosition(const void * str1_struct, const void * str2_struct) {//
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
