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
    choose_game_mode            = 0,
    findout_character           = 1,
    describe_character          = 2,
    show_graph                  = 3,
    waiting_for_answer          = 4,
    process_answer              = 5,
    add_character               = 6,
//******************************************//
    tree_allright               = 0,
    akinator_allright           = 0,
    unexpected_behavior         = -1,
    akinator_cannot_open_file   = -2,
    null_ptr_to_node            = -3,
    invalid_user_input          = -4,
};





#endif
