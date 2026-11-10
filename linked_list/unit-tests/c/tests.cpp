#include "../../h/list_handlers.h"
#include "../../h/list_dumpers.h"
#include "../h/test_info.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//тест создает рандомный список целых числел длиной от 0 до 32
//потом создает массив целых чисел случайных в диапазоне целых числел. Все нули - pop,
//остальные - пуши. Вероятность нуля >~ 30%
LIST_TEST_RESULTS RunRundomPushPopTest () {
    list_struct list = {};
    HandleListConstruct_list_handlers(&list);

    srand(time(NULL));

    size_t num_of_tests = (rand() % (32 - 0 + 1)) + 0;
    int * command_args =   (int *) calloc(sizeof(int), num_of_tests);
    for (size_t i = 0; i < num_of_tests; i++) {
        command_args[i] = (rand() % (100 - (-100) + 1)) - 100;
        if (command_args[i] % 3 == 0) {
            command_args[i] = 0;
        }
    }
    int val = 0;
    for (size_t i = 0; i < num_of_tests; i++) {
        if (command_args[i] == 0) {
            HandleListPop_list_handlers(&list, &val);
            continue;
        }
        else {
            HandleListPush_list_handlers(&list, command_args[i]);
        }
    }
    size_t next_index = 0;
    for (size_t i = 0; i < num_of_tests; i++) {
        if(command_args[i] == 0) continue;
        if (list.buffer[next_index].el_value != command_args[i]) {
            return error_in_push_pop;
        }
        next_index = list.buffer[next_index].next_index;
    }

    CreateGraphFile_list_dumpers(&list);

    return list_test_allright;
}

LIST_TEST_RESULTS RunRandomInsertByIdxTest() {
    list_struct list = {};
    HandleListConstruct_list_handlers(&list);


    CreateGraphFile_list_dumpers(&list);
    return list_test_allright;
}
