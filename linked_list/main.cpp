#include "h/list_handlers.h"
#include "h/list_dumpers.h"

int main() {
    list_struct myFirstList = {};
    HandleListConstruct_list_handlers(&myFirstList);
    HandleListPush_list_handlers(&myFirstList, 1);
    HandleListPush_list_handlers(&myFirstList, 2);
    HandleListPush_list_handlers(&myFirstList, 67);
    HandleListPush_list_handlers(&myFirstList, 4);
    HandleListPush_list_handlers(&myFirstList, 5);
    HandleInsertByIndex_list_handlers   (&myFirstList, 0 , -12);
    HandleInsertByIndex_list_handlers   (&myFirstList, 3 , -12);
    CreateGraphFile_list_dumpers(&myFirstList);


}
