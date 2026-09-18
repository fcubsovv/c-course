#include <stdio.h>

int * BubbleSort(int * array, int len) {
    int buffer = 0;
    int exchangings = 0;
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len - 1 - i; j++) {
            if (array[j] > array[j+1]) {
                buffer = array[j];
                array[j] = array[j+1];
                array[j+1] = buffer;
                exchangings = 1;
            }
        }
        if (exchangings == 0) {
            break;
        }
        exchangings = 0;
    }
    return array;
}

