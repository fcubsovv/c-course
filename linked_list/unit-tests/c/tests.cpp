#include "../h/tests.h"
#define GETNAME(x) #x

list_struct CreateRundomList() {
    list_struct list = {};
    HandleListConstruct_list_handlers(&list);
    srand(time(NULL));

    size_t num_of_tests = (rand() % (16 - 0 + 1)) + 0;
    int * command_args = (int *) calloc(sizeof(int), num_of_tests);
    int * test_answer =  (int *) calloc(sizeof(int), num_of_tests);
    for (size_t i = 0; i < num_of_tests; i++) {
        command_args[i] = (rand() % (100 - (-100) + 1)) - 100;
        if (command_args[i] % 3 == 0) {
            command_args[i] = 0;
        }
    }
    int val = 0;
    size_t current_answer_index = 0;

    for (size_t i = 0; i < num_of_tests; i++) {
        if (command_args[i] == 0) {
            LIST_ERRORS err = HandleListPop_list_handlers(&list, &val);
            if (err == allright_list && current_answer_index != 0) {
                current_answer_index--;
                test_answer[current_answer_index] = 0;
            }
            continue;
        }
        else {
            LIST_ERRORS err = HandleListPush_list_handlers(&list, command_args[i]);
            if (err == allright_list) {
                test_answer[current_answer_index] = command_args[i];
                current_answer_index++;
            }
        }
    }


    return list;
}

//тест создает рандомный список целых числел длиной от 0 до 32
//потом создает массив целых чисел случайных в диапазоне целых числел. Все нули - pop,
//остальные - пуши. Вероятность нуля >~ 30%
test_params RunRundomPushPopTest () {
    list_struct list = {};
    HandleListConstruct_list_handlers(&list);

    srand(time(NULL));

    size_t num_of_tests = (rand() % (32 - 0 + 1)) + 0;
    int * command_args = (int *) calloc(sizeof(int), num_of_tests);
    int * test_answer =  (int *) calloc(sizeof(int), num_of_tests);
    for (size_t i = 0; i < num_of_tests; i++) {
        command_args[i] = (rand() % (100 - (-100) + 1)) - 100;
        if (command_args[i] % 3 == 0) {
            command_args[i] = 0;
        }
    }
    int val = 0;
    size_t current_answer_index = 0;


    for (size_t i = 0; i < num_of_tests; i++) {
        if (command_args[i] == 0) {
            LIST_ERRORS err = HandleListPop_list_handlers(&list, &val);
            if (err == allright_list && current_answer_index != 0) {
                current_answer_index--;
                test_answer[current_answer_index] = 0;
            }
            continue;
        }
        else {
            LIST_ERRORS err = HandleListPush_list_handlers(&list, command_args[i]);
            if (err == allright_list) {
                test_answer[current_answer_index] = command_args[i];
                current_answer_index++;
            }
        }
    }

    int n = num_of_tests;

    char * str = (char *) calloc(256, sizeof(char));
    char * str_ptr = str;
    int offset = 0;

    for (int i = 0; i < n; i++) {
        int written = snprintf(str + offset, 256 - offset, "%d, ", test_answer[i]);
        if (written < 0) {
            break;
        }
        offset += written;
    }

    LIST_TEST_RESULTS res_code = list_test_allright;

    test_params result = {list_test_allright};
    result.expected_result = str;
    result.filename = "scheme1.png";

    size_t current_node_index = 0;

    for (size_t i = 0; i < current_answer_index; i++) {
        current_node_index = list.buffer[current_node_index].next_index;

        if (current_node_index == 0) {
            res_code = error_in_push_pop;
            break;
        }
        if (list.buffer[current_node_index].el_value != test_answer[i]) {
            res_code = error_in_push_pop;
            break;
        }
    }

    if (res_code == list_test_allright &&
        list.buffer[current_node_index].next_index != 0) {
        res_code = error_in_push_pop;
    }
    result.res_code = res_code;
    CreateGraphFile_list_dumpers(&list);
    free(command_args);
    free(test_answer);

    return result;
}
//тест создает рандомный list
//потом создает массив комманд и индексов, если число больше нуля - оно вставляется по индексу, если меньше нуля - выполняется pull по этому индексу
test_params RunRandomInsertByIdxTest() {
    list_struct list = CreateRundomList();


    srand(time(NULL));
    size_t index = 0;
    int val = 0;
    size_t num_of_tests = (rand() % (8 - 0 + 1)) + 0;
    printf("%d\n", num_of_tests);
    int * command_args = (int *) calloc(sizeof(int), num_of_tests);
    int * indexes = (int *) calloc(sizeof(int), num_of_tests);

    for (size_t i = 0; i < num_of_tests; i++) {
        command_args[i] = (rand() % (100 - (-100) + 1)) - 100;
        index = (rand() % (list.length - 1));
        indexes[i] = index;
        if ( command_args[i] >=0 ) HandleInsertByIndex_list_handlers(&list, index, command_args[i]);
        else HandlePullElByIndex_list_handles(&list, index, &val);
    }
    int n = num_of_tests;

    char * str = (char *) calloc(256, sizeof(char));
    char * str_ptr = str;
    int offset = 0;

    for (int i = 0; i < n; i++) {
        int written = snprintf(str + offset, 256 - offset, "(%d, %d)", command_args[i], indexes[i]);

        if (written < 0) {
            break;
        }
        offset += written;
    }



    CreateGraphFile_list_dumpers(&list);
    free(command_args);
    return {list_test_allright, str, "scheme2.png"};
}
