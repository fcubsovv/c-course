#include "../h/list_handlers.h"

//______________________________________________________________________________________________________________________________________

static LIST_ERRORS ExpandList(list_struct * list) {
    if (list->length + 1 < list->capacity) return allright_list;
    size_t old_capacity = list->capacity;
    size_t new_capacity = old_capacity*2;

    list_elem * arr = (list_elem *)realloc(list->buffer, new_capacity * sizeof(list_elem));
    if (arr == NULL) return error_getting_memory;

    list->buffer = arr;
    list->capacity = new_capacity;

    for (size_t i = old_capacity; i < new_capacity; i++) {
        list->buffer[i].el_value = POISON_VAL;
        list->buffer[i].prev_index = FREE;
        list->buffer[i].next_index = (i + 1) % new_capacity;
    }
    list->empty_head = old_capacity;
    return allright_list;
}

static size_t FindCurrentIndex(list_struct * list, size_t index) {
     size_t current_idx_in_buffer = 0;
    for (size_t i = 0; i <= index; i++) current_idx_in_buffer = list->buffer[current_idx_in_buffer].next_index;
    return current_idx_in_buffer;
}

//____________________________________________________________________________________________________________________________________________________________________

LIST_ERRORS HandleListConstruct_list_handlers   (list_struct * list) {
    list->capacity = LIST_CAPACITY;

    list_elem * arr = (list_elem*)calloc(sizeof(list_elem), list->capacity);
    if (arr == NULL) {
        DisplayListError(error_getting_memory);
        return error_getting_memory;
    };
    list->buffer = arr;
    list->buffer[0] = {};
    list->buffer[0].el_value = POISON_VAL;
    list->tail = 0;
    list->empty_head = 1;
    for (size_t i = 1; i < LIST_CAPACITY; i++) {
        list->buffer[i].next_index = (i+1)%list->capacity;
        list->buffer[i].prev_index = FREE;
        list->buffer[i].el_value = POISON_VAL;
    }
    list->length = 0;
    return allright_list;
}

LIST_ERRORS HandleListPush_list_handlers        (list_struct * list, int value) {
    DisplayListError(ExpandList(list));
    size_t empty_head = list->empty_head;
    list->empty_head = list->buffer[list->empty_head].next_index;
    size_t old_tail = list->tail;
    list->buffer[old_tail].next_index = empty_head;
    list->tail = empty_head;
    list->buffer[list->tail].el_value = value;
    list->buffer[list->tail].prev_index = old_tail;
    list->buffer[list->tail].next_index = 0;
    list->length++;
    return allright_list;
}

LIST_ERRORS HandleListPop_list_handlers         (list_struct * list, int * gotten_val) {
    if (list->tail == 0) {
        return pop_empty_list;
    }
    *gotten_val = list->buffer[list->tail].el_value;
    size_t old_empty_head = list->empty_head;
    size_t old_tail = list->tail;
    list->tail = list->buffer[list->tail].prev_index;
    list->buffer[list->tail].next_index = 0;
    list->empty_head = old_tail;
    list->buffer[list->empty_head].next_index = old_empty_head;
    list->buffer[list->empty_head].prev_index = FREE;
    list->buffer[list->empty_head].el_value = POISON_VAL;
    list->length--;
    return allright_list;
}

LIST_ERRORS HandleInsertByIndex_list_handlers   (list_struct * list, size_t index, int value) {

    if(index > list->length) return tryind_insert_beyond_limits;
    ExpandList(list);

    if (index == list->length) return HandleListPush_list_handlers(list, value);

    size_t current_idx_in_buffer = FindCurrentIndex(list, index);


    size_t empty_el = list->empty_head;
    size_t prev_idx = list->buffer[current_idx_in_buffer].prev_index;

    list->empty_head = list->buffer[list->empty_head].next_index;

    list->buffer[empty_el].el_value = value;
    list->buffer[empty_el].next_index = current_idx_in_buffer;
    list->buffer[empty_el].prev_index = prev_idx;

    list->buffer[current_idx_in_buffer].prev_index = empty_el;
    list->buffer[prev_idx].next_index = empty_el;
    list->length++;
    return allright_list;
}

LIST_ERRORS HandlePullElByIndex_list_handles    (list_struct * list, size_t index, int * gotten_val) {
    if (index >= list->length) return pulling_beyond_limits;

    size_t current_idx_in_buffer = FindCurrentIndex(list, index);

    *gotten_val = list->buffer[current_idx_in_buffer].el_value;
    list->buffer[current_idx_in_buffer].el_value = POISON_VAL;
    size_t prev_el_idx = list->buffer[current_idx_in_buffer].prev_index;
    if (current_idx_in_buffer == list->tail) list->tail = prev_el_idx;

    size_t next_el_idx = list->buffer[current_idx_in_buffer].next_index;
    list->buffer[prev_el_idx].next_index = next_el_idx;
    if (next_el_idx != 0) list->buffer[next_el_idx].prev_index = prev_el_idx;


    size_t old_empty_head = list->empty_head;
    list->empty_head = current_idx_in_buffer;
    list->buffer[list->empty_head].prev_index = FREE;
    list->buffer[list->empty_head].next_index = old_empty_head;
    list->length--;


    return allright_list;
}

LIST_ERRORS HandleDestruct_list_handlers        (list_struct * list) {

    list->length = 0;
    list->capacity = 0;
    list->tail = 0;
    list->empty_head = 0;
    free(list->buffer);
    list->buffer = NULL;

    return allright_list;
}
