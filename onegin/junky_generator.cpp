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

int GetRandomGroupWithMinLines(const lines_array_struct * rhymed_lines, int number_of_groups, size_t min_lines) {
    int group_idx = 0;
    do {
        group_idx = rand() % number_of_groups;
    } while (rhymed_lines[group_idx].lines_count < min_lines);

    return group_idx;
}

line_struct GetRandomLineFromGroup(const lines_array_struct * rhymed_lines, int group_idx) {
    size_t count = rhymed_lines[group_idx].lines_count;
    return rhymed_lines[group_idx].lines[rand() % count];
}


line_struct * GenerateSomeJunk (line_struct * lines_array, size_t lines_count, size_t how_many_generate) {
    int number_of_groups = 1;
    for (size_t i = 1; i < lines_count; i++) {
        if ((CompareLastThreeSymbols(&lines_array[i], &lines_array[i-1]) != 0)) {
            number_of_groups++;
        }
    }
    lines_array_struct * rhymed_lines = (lines_array_struct *)calloc(number_of_groups, sizeof(lines_array_struct));
    line_struct * verse  = (line_struct *)calloc(how_many_generate*14, sizeof(line_struct));
    size_t group_index = 0;
    rhymed_lines[0].lines = (line_struct *) calloc(lines_count, sizeof(line_struct));
    rhymed_lines[0].lines[0] = lines_array[0];
    rhymed_lines[0].lines_count = 1;
    for (size_t i = 1; i < lines_count; i++) {
        if ( CompareLastThreeSymbols(&lines_array[i], &lines_array[i-1])) {
            group_index++;
            rhymed_lines[group_index].lines = (line_struct *) calloc(lines_count, sizeof(line_struct));;
        }
        size_t current_idx = rhymed_lines[group_index].lines_count;
        rhymed_lines[group_index].lines[current_idx] = lines_array[i];
        rhymed_lines[group_index].lines_count++;
    }
    srand(time(NULL));

    int num_of_A_group = GetRandomGroupWithMinLines(rhymed_lines, number_of_groups, 5);
    int num_of_B_group = GetRandomGroupWithMinLines(rhymed_lines, number_of_groups, 5);

    int num_of_G_group = GetRandomGroupWithMinLines(rhymed_lines, number_of_groups, 5);

    int num_of_V_group = GetRandomGroupWithMinLines(rhymed_lines, number_of_groups, 5);
    int num_of_D_group = GetRandomGroupWithMinLines(rhymed_lines, number_of_groups, 5);
    int num_of_E_group = GetRandomGroupWithMinLines(rhymed_lines, number_of_groups, 5);
    int num_of_J_group = GetRandomGroupWithMinLines(rhymed_lines, number_of_groups, 5);
    for (size_t i = 0; i < how_many_generate; i++) {
        verse[i*14]     = GetRandomLineFromGroup(rhymed_lines, num_of_A_group);
        verse[1 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_B_group);
        verse[2 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_A_group);
        verse[3 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_B_group);
        verse[4 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_V_group);
        verse[5 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_V_group);
        verse[6 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_G_group);
        verse[7 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_G_group);
        verse[8 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_D_group);
        verse[9 + i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_E_group);
        verse[10+ i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_E_group);
        verse[11+ i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_D_group);
        verse[12+ i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_J_group);
        verse[13+ i*14] = GetRandomLineFromGroup(rhymed_lines, num_of_J_group);
    }
    return verse;
}


#endif
