#ifndef TREE_READER
#define TREE_READER
#include "tree_declaration.h"
#include <stdio.h>
#include "../h/tree-dumpers.h"
#include <cstdlib>
#include "../../global_utils/h/filework.h"
#include "helpers.h"

AKINATOR_TREE_ERRORS ReadTreeFromFile(const char * filename, Node * TreeNode);

#endif
