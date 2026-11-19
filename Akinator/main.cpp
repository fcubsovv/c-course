#include "h/tree_declaration.h"
#include "h/tree-reader.h"
#include "h/akinator-modes.h"

int main(void) {
    Node TreeNode = {};
    char * answer = (char *) calloc (128, sizeof(char));
    ReadTreeFromFile("test-data/clash-graph.txt", &TreeNode);
   // HandleFindOutCharacterMode(&TreeNode, answer);
    CreateTreeGraph (&TreeNode) ;
    HandleAddCharacterMode(&TreeNode, answer);
    CreateTreeGraph (&TreeNode) ;
    return 0;
}
