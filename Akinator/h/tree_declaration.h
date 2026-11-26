#ifndef TREE_DECLARATION
#define TREE_DECLARATION
#include <stdint.h>

struct Node {

    char message[256];
    Node * right;
    Node * left;
    Node * parent;
    uint64_t identifier;

};

enum AKINATOR_TREE_ERRORS {
    akinator_choose_mode            = 0,
    akinator_findout_add_character  = 1,
    akinator_describe_character     = 2,
    akinator_compare_character      = 3,
    akinator_end                    = 4,
//******************************************//
    tree_allright               = 0,
    akinator_allright           = 0,
    unexpected_behavior         = -1,
    akinator_cannot_open_file   = -2,
    null_ptr_to_node            = -3,
    invalid_user_input          = -4,
    null_ptr_to_line            = -5,
    invalid_game_type           = -6,
    error_allocating_memory     = -7,
    akinator_window_closed      = -8,
};



#endif
