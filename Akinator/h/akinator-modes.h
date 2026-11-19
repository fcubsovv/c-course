#ifndef AKINATOR_MODES
#define AKINATOR_MODES
#include "tree_declaration.h"
#include <stdio.h>
#define POSITIVE_ANS "+"
#define NEGATIVE_ANS "-"
#include "helpers.h"

AKINATOR_TREE_ERRORS HandleFindOutCharacterMode(Node * TreeNode, char * line, Node ** found_node) ;
AKINATOR_TREE_ERRORS HandleDescribingCharacterMode(Node * TreeNode, char * line) ;
AKINATOR_TREE_ERRORS HandleAddCharacterMode (Node * TreeNode, char * line);

#endif
