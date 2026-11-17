#ifndef LIST_DECLARATION
#define LIST_DECLARATION
#include <cstdlib>
#include <stdio.h>

#define POISON_VAL -6767
#define FREE -1

enum LIST_ERRORS {
    cannot_open_file = -1,
    pop_empty_list = -2,
    tryind_insert_beyond_limits = -3,
    error_getting_memory = -4,
    pulling_beyond_limits = -5,
    extra_el_in_list = -6,
    prev_next_error = -7,
    tail_error = -8,
    error_prev_in_free_el = -9,
    error_capacity = -10,
    allright_list = 0,
};

struct list_elem {
    int el_value;
    int prev_index;
    size_t next_index;
};

struct list_struct {
    size_t length;
    size_t capacity;
    size_t tail;
    size_t empty_head;
    list_elem * buffer;
};

const size_t LIST_CAPACITY = 16;


#endif
