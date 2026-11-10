#ifndef LIST_HANDLERS
#define LIST_HANDLERS
#include "list_decklaration.h"

LIST_ERRORS HandleListConstruct_list_handlers (list_struct * list);//+

LIST_ERRORS HandleListPush_list_handlers      (list_struct * list, int value);//+

LIST_ERRORS HandleListPop_list_handlers       (list_struct * list, int * gotten_val);//+

LIST_ERRORS HandleInsertByIndex_list_handlers (list_struct * list_struct, size_t index, int value);

LIST_ERRORS HandlePullElByIndex_list_handles (list_struct * list, size_t index, int * gotten_val);

LIST_ERRORS HandleInsertSublist_list_handles (list_struct * main_list, list_struct * sublist);


#endif
