#include "../h/list_handlers.h"



LIST_ERRORS HandleListConstruct_list_handlers   (list_struct * list) {
    list->capacity = LIST_CAPACITY;
    list->buffer = (list_elem*)calloc(sizeof(list_elem), list->capacity);
    list->buffer[0] = {};
    list->buffer[0].el_value = POISON_VAL;
    list->tail = 0;
    list->empty_head = 1;
    for (size_t i = 1; i < LIST_CAPACITY; i++) {
        list->buffer[i].next_index = (i+1)%list->capacity;
        list->buffer[i].prev_index = FREE;
    }
    list->length = 0;
    return allright_list;
}

LIST_ERRORS HandleListPush_list_handlers         (list_struct * list, int value) {
    if (list->capacity == list->length+1) {
        list->capacity*=2;
        list_elem * newarr = (list_elem *)realloc(list->buffer, list->capacity*sizeof(list_elem));
        if (newarr == NULL) return error_getting_memory;
        list->buffer = newarr;

    }
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

LIST_ERRORS HandleListPop_list_handlers          (list_struct * list, int * gotten_val) {
    if (list->capacity/4 == list->length+1) {
        list->capacity/=2;
        list_elem * newarr = (list_elem *)realloc(list->buffer, list->capacity*sizeof(list_elem));
        if (newarr == NULL) return error_getting_memory;
        list->buffer = newarr;

    }
    *gotten_val = list->buffer[list->tail].el_value;
    if (list->tail == 0) {
        return pop_empty_list;
    }
    size_t old_empty_head = list->empty_head;
    size_t old_tail = list->tail;
    list->tail = list->buffer[list->tail].prev_index;
    list->buffer[list->tail].next_index = 0;
    list->empty_head = old_tail;
    list->buffer[list->empty_head].next_index = old_empty_head;
    list->buffer[list->empty_head].prev_index = -1;
    list->buffer[list->empty_head].el_value = 0;
    list->length--;
    return allright_list;
}

LIST_ERRORS HandleInsertByIndex_list_handlers   (list_struct * list, size_t index, int value) {
    if (list->capacity/4 == list->length+1) {
        list->capacity/=2;
        list_elem * newarr = (list_elem *)realloc(list->buffer, list->capacity*sizeof(list_elem));
        if (newarr == NULL) return error_getting_memory;
        list->buffer = newarr;

    }
    if (list->empty_head == 0) return tryind_insert_beyond_limits;
    if (list->capacity == list->length-1) {
        list->capacity*=2;
        list_elem * newarr = (list_elem *)realloc(list->buffer, list->capacity*sizeof(list_elem));
        if (newarr == NULL) return error_getting_memory;
        list->buffer = newarr;

    }
    if(index > list->length) {
        return tryind_insert_beyond_limits;
    }
    size_t current_idx_in_buffer = 0;
    for (size_t i = 0; i <= index; i++) {
        current_idx_in_buffer = list->buffer[current_idx_in_buffer].next_index;
    }

    size_t empty_el = list->empty_head;
    size_t prev_idx = list->buffer[current_idx_in_buffer].prev_index;
    size_t next_idx = list->buffer[current_idx_in_buffer].next_index;

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
    size_t current_idx_in_buffer = 0;
    for (size_t i = 0; i <= index; i++) {
        current_idx_in_buffer = list->buffer[current_idx_in_buffer].next_index;
    }
    size_t prev_el_idx = list->buffer[current_idx_in_buffer].prev_index;
    size_t next_el_idx = list->buffer[current_idx_in_buffer].next_index;
    list->buffer[prev_el_idx].next_index = next_el_idx;
    list->buffer[next_el_idx].prev_index = prev_el_idx;

    size_t old_empty_head = list->empty_head;
    list->empty_head = current_idx_in_buffer;
    list->buffer[list->empty_head].prev_index = -1;
    list->buffer[list->empty_head].next_index = old_empty_head;
    list->buffer[old_empty_head].prev_index = list->empty_head;
    list->length--;


    return allright_list;
}

LIST_ERRORS HandleInsertSublist_list_handles    (list_struct * main_list, list_struct * sublist, size_t idx) {//дописать тут либо реаллок либо чет там вставляем на пустые места поэлементно
    size_t current_idx_in_buffer = 0;
    for (size_t i = 0; i < idx; i++) {
        current_idx_in_buffer = main_list->buffer[current_idx_in_buffer].next_index;
    }

    size_t next_index = main_list->buffer[current_idx_in_buffer].next_index;



    return allright_list;
}


LIST_ERRORS HandleDestruct_list_handlers (list_struct * list) {

    list->length = 0;
    list->capacity = 0;
    list->tail = 0;
    list->empty_head = 0;
    free(list->buffer);//error

    return allright_list;
}
