#ifndef JUNKY
#define JUNKY
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "comparators.cpp"
#include "../global_utils/user_string.cpp"

struct lines_array_struct {
    line_struct * lines;
    size_t lines_count;
};

line_struct * GenerateSomeJunk (line_struct * lines_array, size_t lines_count, size_t how_many_generate) {
    int number_of_groups = 1;
    for (size_t i = 1; i < lines_count; i++) {
        if (CompareLastThreeSymbols(lines_array[i].str, lines_array[i-1].str) != 0) {
            number_of_groups++;
        }
    }
    lines_array_struct * rhymed_lines = (lines_array_struct *)calloc(number_of_groups, sizeof(lines_array_struct));
    line_struct * verse  = (line_struct *)calloc(how_many_generate*14, sizeof(line_struct));
    size_t group_index = 0;
    rhymed_lines[0].lines = {};
    rhymed_lines[0].lines[0] = lines_array[0];
    rhymed_lines[0].lines_count = 1;
    for (size_t i = 1; i < lines_count; i++) {
        if (CompareLastThreeSymbols(lines_array[i].str, lines_array[i-1].str) != 0) {
            group_index++;
            rhymed_lines[group_index].lines = {};
        }
        rhymed_lines[group_index].lines[0] = lines_array[i];
        rhymed_lines[group_index].lines_count++;
    }
    srand(time(NULL));
    int num_of_A_group = rand() % number_of_groups;// add check if enought samples
    int num_of_B_group = rand() % number_of_groups;
    int num_of_V_group = rand() % number_of_groups;
    int num_of_G_group = rand() % number_of_groups;
    int num_of_D_group = rand() % number_of_groups;
    int num_of_E_group = rand() % number_of_groups;
    int num_of_J_group = rand() % number_of_groups;

    for (size_t i = 0; i < how_many_generate; i++) {
        verse[i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[1 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[2 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[3 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[4 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[5 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[6 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[7 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[8 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[9 + i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[10+ i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[11+ i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[12+ i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
        verse[13+ i*14] = rhymed_lines[num_of_A_group].lines[rand() % rhymed_lines[num_of_A_group].lines_count];
    }

    return verse;
}

#endif
