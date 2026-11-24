#include "h/tree_declaration.h"
#include "h/tree-reader.h"
#include "h/akinator-modes.h"

int main(void) {
    Node TreeNode = {};
    char * answer = (char *) calloc (128, sizeof(char));
    ReadTreeFromFile("test-data/clash-graph.txt", &TreeNode);
    CreateTreeGraph (&TreeNode) ;
    HandleGameModes(&TreeNode, akinator_describe_character);
    CreateTreeGraph (&TreeNode) ;
    return 0;
}
