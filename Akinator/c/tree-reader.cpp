#include "../h/tree-reader.h"


AKINATOR_TREE_ERRORS ReadNode(Node * TreeNode, char ** str_ptr) {
    if (TreeNode == NULL) return null_ptr_to_node;
    int offset = 0;
    sscanf(*str_ptr, " (%256[^()]%n", TreeNode->message, &offset);
    TreeNode->identifier = HashString(TreeNode->message);
    (*str_ptr)+=offset;
    if ((**str_ptr) == ')') {
        (*str_ptr)++;
        return akinator_allright;
    }
    else {
        TreeNode->left = (Node*)calloc(1, sizeof(Node));
        TreeNode->left->parent = TreeNode;

        AKINATOR_TREE_ERRORS err = ReadNode(TreeNode->left, str_ptr);

        TreeNode->right = (Node*)calloc(1, sizeof(Node));
        TreeNode->right->parent = TreeNode;
        err = ReadNode(TreeNode->right, str_ptr);

        if ((**str_ptr) == ')') {
            (*str_ptr)++;
            return akinator_allright;
        }

    }
    return akinator_allright;
}



AKINATOR_TREE_ERRORS ReadTreeFromFile(const char * filename, Node * TreeNode) {

    FILE * file = fopen(filename, "r");
    if (file == NULL) return akinator_cannot_open_file;
    char * line = (char*)calloc(128,sizeof(char));
    int offset = 0;

    buffer_struct buffer = ReadFromFileToBuffer(filename);
    char * str_ptr = (char *)buffer.buffer;
    int identifier = 0;
    ReadNode(TreeNode, &str_ptr);

    return akinator_allright;

};
