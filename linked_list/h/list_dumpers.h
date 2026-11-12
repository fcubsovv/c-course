#ifndef LIST_DUMPERS
#define LIST_DUMPERS
#include "list_decklaration.h"
#include "../unit-tests/h/test_info.h"

LIST_ERRORS ListElDump_list_dumpers(list_elem * list_elem);

LIST_ERRORS ListDump_list_dumpers(list_struct * list_struct);

LIST_ERRORS CreateGraphFile_list_dumpers(list_struct * list);

LIST_ERRORS GenerateTestsHtmlFile(test_params push_pop_test, test_params insert_pull_test);

#endif
