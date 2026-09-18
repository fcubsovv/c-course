#include <stdio.h>
#include "swap.cpp"


void * user_bsort(void * array, size_t len, size_t size, int (*compar)(const void *, const void *)) {
    int exchangings = 0;
    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len - 1 - i; j++) {

            if (compar(((unsigned char * )(array) + j*size), ((unsigned char * )(array) + (j+1)*size)) > 0) {
                swap(((unsigned char * )(array) + j*size), ((unsigned char * )(array) + (j+1)*size), size);
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

