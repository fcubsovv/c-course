#include "../h/list_dumpers.h"

LIST_ERRORS ListElDump_list_dumpers(list_elem * list_elem) {
    printf("LIST EL VALUE: %d\n", list_elem->el_value);
    printf("LIST EL PREV: %d\n", list_elem->prev_index);
    printf("LIST EL NEXT: %zu\n", list_elem->next_index);
    return allright_list;
}

LIST_ERRORS ListDump_list_dumpers(list_struct * list_struct) {

    printf("LIST CAPACITY: %zu\n", list_struct->capacity);
    printf("LIST HEAD: \n");
    ListElDump_list_dumpers(&list_struct->buffer[0]);
    printf("LIST EMPTY HEAD: \n");
    ListElDump_list_dumpers(&list_struct->buffer[list_struct->empty_head]);

    printf("LIST LENGTH: %zu\n", list_struct->length);
    for (size_t i = 0; i < list_struct->capacity; i++) {
        ListElDump_list_dumpers(&list_struct->buffer[i]);
    }

    return allright_list;
}

LIST_ERRORS CreateGraphFile_list_dumpers(list_struct * list) {

    FILE * fileopen = fopen("graph.dot", "w");
    if(fileopen == NULL) return cannot_open_file;

    fprintf(fileopen, "digraph RoundedSplitGraph {\n");
    fprintf(fileopen, "rankdir=LR; \n");
    fprintf(fileopen, "node [shape=Mrecord, style=filled, fillcolor=\"#f9f9f9\", color=\"#2c3e50\", fontname=\"Arial\", fontsize=11];\n");
    const char * color = 0;
    for (size_t i = 0; i < list->capacity; i++) {
    list_elem current = list->buffer[i];
        if (i == 0) {
            color = "#2adb77";
        } else if (current.prev_index == FREE) {
            color = "#c9c7c4";

        } else {
            color = "#ff4800";
        }

        fprintf(fileopen, "Node%zu [label=\" val %d  | { prev %d | next %zu }\" fillcolor=\"%s\"]; \n", i, current.el_value, current.prev_index, current.next_index, color);
    }
    for (size_t i = 0; i < list->capacity; i++) {
        list_elem current = list->buffer[i];
        if (current.next_index == 0) {
            fprintf(fileopen, "Node%zu -> Node%zu [color=red, constraint=false];\n", i, current.next_index);
        } else {
            fprintf(fileopen, "Node%zu -> Node%zu [color=blue];\n", i, current.next_index);
        }
    }
    list_elem current = 0;
     for (size_t i = 0; i < list->length; i++) {
        list_elem current = list->buffer[i];
        fprintf(fileopen, "Node%zu -> Node%d [color=gray, style=dashed];\n", i, current.prev_index);
    }


    fprintf(fileopen, "}\n");
    fclose(fileopen);
    return allright_list;
}
