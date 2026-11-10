#include <cstdlib>
#include <stdio.h>


enum LIST_ERRORS {
    allright_list = 0,
};

struct list_elem {
    int el_value;
    size_t prev_index;
    size_t next_index;
    size_t index;
};

struct list_struct {
    size_t capacity;
    list_elem * list_head;
    list_elem * list_tail;
    list_elem * empty_list_head;
    size_t list_length;
    list_elem * list_el_buffer;
};

const size_t LIST_CAPACITY = 16;

LIST_ERRORS ListConstructor (list_struct * list_struct) {
    list_struct->capacity = LIST_CAPACITY;
    list_struct->list_el_buffer = (list_elem*)calloc(sizeof(list_elem), list_struct->capacity);
    list_struct->list_el_buffer[0] = {
        -6767, 0, 0, 0,
    };
    list_struct->list_head = &list_struct->list_el_buffer[0];
    for (size_t i = 1; i < list_struct->capacity; i++) {
        list_struct->list_el_buffer[i] = {};
        list_struct->list_el_buffer[i].el_value = -6767;
        list_struct->list_el_buffer[i].prev_index = i - 1;
        list_struct->list_el_buffer[i].next_index =  (i+1) % list_struct ->capacity;
        list_struct->list_el_buffer[i].index = i;
    }
    list_struct -> empty_list_head = &list_struct->list_el_buffer[1];
    list_struct -> list_tail = list_struct -> list_head;
    return allright_list;
}

LIST_ERRORS ListPush (list_struct * list_struct, int value) {
    list_struct -> empty_list_head->el_value = value;
    list_struct -> empty_list_head->prev_index = (list_struct -> list_tail)->index;
    size_t next_empty_head = list_struct -> empty_list_head->next_index;
    list_struct -> empty_list_head->next_index = 0;
    list_struct -> list_tail->next_index =  list_struct -> empty_list_head ->index;
    list_struct -> list_tail = list_struct -> empty_list_head;
    list_struct -> empty_list_head = &(list_struct->list_el_buffer)[next_empty_head];
    return allright_list;
}

LIST_ERRORS ListPop(list_struct * list_struct, int * gotten_val) {
    *gotten_val = list_struct->list_tail->el_value;

    size_t next_tail = list_struct ->list_tail->prev_index;

    list_struct->list_el_buffer[next_tail].next_index = 0;

    return allright_list;
}

LIST_ERRORS InsertByIndex (list_struct * list_struct, size_t index, int value) {
    return allright_list;
}

LIST_ERRORS ListElDump(list_elem * list_elem) {
    printf("LIST EL VALUE: %d\n", list_elem->el_value);
    printf("LIST EL PREV: %zu\n", list_elem->prev_index);
    printf("LIST EL NEXT: %zu\n", list_elem->next_index);
    return allright_list;
}

LIST_ERRORS ListDump(list_struct * list_struct) {

    printf("LIST CAPACITY: %zu\n", list_struct->capacity);
    printf("LIST HEAD: \n");
    ListElDump(list_struct->list_head);
    printf("LIST EMPTY HEAD: \n");
    ListElDump(list_struct->empty_list_head);

    printf("LIST LENGTH: %zu\n", list_struct->list_length);
    for (size_t i = 0; i < list_struct->capacity; i++) {
        ListElDump(&list_struct->list_el_buffer[i]);
    }

    return allright_list;
}

LIST_ERRORS CreateGraphFile(list_struct * list_struct) {

    FILE * fileopen = fopen("graph.dot", "w");
    fprintf(fileopen, "digraph RoundedSplitGraph {\n");
    fprintf(fileopen, "node [shape=Mrecord, style=filled, fillcolor=\"#f9f9f9\", color=\"#2c3e50\", fontname=\"Arial\", fontsize=11];\n");

    for (size_t i = 0; i < list_struct->capacity - 1; i++) {
        fprintf(fileopen, "Node%zu [label=\" %d  | { %zu | %zu }\"]; \n", i, list_struct->list_el_buffer[i].el_value,  list_struct->list_el_buffer[i].prev_index, list_struct->list_el_buffer[i].next_index);
        fprintf(fileopen, " Node%zu [label=\" %d  | { %zu | %zu }\"];\n", list_struct->list_el_buffer[i].next_index, list_struct->list_el_buffer[list_struct->list_el_buffer[i].next_index].el_value,  list_struct->list_el_buffer[list_struct->list_el_buffer[i].next_index].prev_index, list_struct->list_el_buffer[list_struct->list_el_buffer[i].next_index].next_index);
        fprintf(fileopen, "Node%zu -> Node%zu\n", i, list_struct->list_el_buffer[i].next_index);
    }

    fprintf(fileopen, "}\n");
    return allright_list;
}

int main() {
    list_struct myFirstList = {};
    ListConstructor(&myFirstList);
    ListPush(&myFirstList, 1);
    ListPush(&myFirstList, 2);
    ListPush(&myFirstList, 3);
    ListPush(&myFirstList, 4);
    ListPush(&myFirstList, 5);
    ListDump(&myFirstList);
    CreateGraphFile(&myFirstList);


}
