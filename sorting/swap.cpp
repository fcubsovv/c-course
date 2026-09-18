#include <stdio.h>
#include <stdlib.h>

int swap (void * first, void * second, size_t size) {
    if (first == second) {
        return 0;
    }
    unsigned char * char_first = (unsigned char *) first;
    unsigned char * char_second = (unsigned char *) second;
    for (size_t i = 0; i < size; i++) {
        unsigned char c = char_first[i] ^ char_second[i];
        char_first[i] = c ^ char_first[i];
        char_second[i] = c ^ char_second[i];
    }
    return 0;
}

int swap_most_optimized (void * first, void * second, size_t size) {
    if (first == second) {
        return 0;
    }
    size_t i = 0;
    size_t steps_8 = size - size % sizeof(uint64_t);
    unsigned char * start = (unsigned char *) first;
    unsigned char * second_start = (unsigned char *) second;

    for (;i < steps_8; i += sizeof(uint64_t)) {
        uint64_t * char_first_8 = (uint64_t *)(start + i);
        uint64_t * char_second_8 = (uint64_t *)(second_start + i);
        uint64_t c = *char_first_8;
        *char_first_8 = *char_second_8;
        *char_second_8 = c;
    }

    if (size - i >= sizeof(uint32_t)) {
        uint32_t * char_first_4 = (uint32_t *)(start + i);
        uint32_t * char_second_4 = (uint32_t *)(second_start + i);
        uint32_t c = *char_first_4;
        *char_first_4 = *char_second_4;
        *char_second_4 = c;
        i += sizeof(uint32_t);
    }
    if (size - i >=sizeof(uint16_t)) {
        uint16_t * char_first_2 = (uint16_t *)(start + i);
        uint16_t * char_second_2 = (uint16_t *)(second_start + i);
        uint16_t c = *char_first_2;
        *char_first_2 = *char_second_2;
        *char_second_2 = c;
        i+=sizeof(uint16_t);
    }
    if (i < size) {
        unsigned char * char_first = (unsigned char *)(start + i);
        unsigned char * char_second = (unsigned char *)(second_start + i);
        unsigned char c = *char_first;
        *char_first = *char_second;
        *char_second = c;
    }
    return 0;
}

int swap_optimized (void * first, void * second, size_t size) {

    size_t i = 0;
    if (first == second) {
        return 0;
    }

    size_t steps_8 = size - size % sizeof(uint64_t);
    unsigned char * start = (unsigned char *) first;
    unsigned char * second_start = (unsigned char *) second;
    for (; i < steps_8; i+=sizeof(uint64_t)) {
        uint64_t * char_first_8 = (uint64_t *)(start + i);
        uint64_t * char_second_8 = (uint64_t *)(second_start + i);
        uint64_t c = *char_first_8 ^ *char_second_8;
        *char_first_8 = c ^ *char_first_8;
        *char_second_8 = c ^ *char_second_8;
    }

    if (size - i >= sizeof(uint32_t)) {
        uint32_t * char_first_4 = (uint32_t *)(start + i);
        uint32_t * char_second_4 = (uint32_t *)(second_start + i);
        uint32_t c = *char_first_4 ^ *char_second_4;
        *char_first_4 = c ^ *char_first_4;
        *char_second_4 = c ^ char_second_4[i];
        i+=sizeof(uint16_t);
    }
    if (size - i >=sizeof(uint16_t)) {
        uint16_t * char_first_2 = (uint16_t *)(start + i);
        uint16_t * char_second_2 = (uint16_t *)(second_start + i);
        uint16_t c = *char_first_2 ^ *char_second_2;
        *char_first_2 = c ^ *char_first_2;
        *char_second_2 = c ^ *char_second_2;
        i+=sizeof(uint16_t);
    }
    if (i < size) {
        unsigned char * char_first = (unsigned char *)(start + i);
        unsigned char * char_second = (unsigned char *)(second_start + i);
        unsigned char c = *char_first ^ *char_second;
        *char_first = c ^ *char_first;
        *char_second = c ^ *char_second;
    }
    return 0;
}
