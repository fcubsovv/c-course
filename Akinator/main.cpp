#include "h/tree_declaration.h"
#include "h/tree-reader.h"
#include "h/game.h"

int main(void) {
    Node TreeNode = {};

    ReadTreeFromFile("test-data/clash-graph.txt", &TreeNode);

    CreateTreeGraph (&TreeNode) ;

    PlayAkinatorGameTerminal(&TreeNode, akinator_terminal_game);

    CreateTreeGraph (&TreeNode) ;
    return 0;
}
