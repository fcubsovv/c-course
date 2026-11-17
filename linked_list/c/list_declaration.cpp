#include "../h/list_decklaration.h"

LIST_ERRORS ListVerify(list_struct * list) {
    size_t current_index = 0;
    size_t count = 0;

    while(1) {
        size_t next_index = list->buffer[current_index].next_index;
        if (next_index == 0) break;
        count++;
        if (count > list->length) return extra_el_in_list;
        if (list->buffer[next_index].prev_index != (int)current_index) return prev_next_error;
        current_index = next_index;
    }
    if (count != list->length) return extra_el_in_list;
    if (current_index != list->tail) return tail_error;


    size_t free = 0;
    for (size_t free_index = list->empty_head; free_index != 0; free_index = list->buffer[free_index].next_index){
        if (list->buffer[free_index].prev_index != FREE ) return error_prev_in_free_el;
        free++;
        if(free >= list->capacity) return error_capacity;
    }

    if (free + list->length + 1 == list->capacity) return error_capacity;
    return allright_list;
}
