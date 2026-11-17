#ifndef TREE_DECLARATION
#define TREE_DECLARATION

struct Node {

    char * message;
    Node * right;
    Node * left;
    Node * parent;

};


enum AKINATOR_ERRORS {
    akinator_allright = 0,
    akinator_cannot_open_file

};



#endif
