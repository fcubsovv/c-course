#include "../h/tree-dumpers.h"
#include <cstddef>
#include <cstdio>


//if node doesn have any kids - it is leaf

AKINATOR_ERRORS CreateTreeDump (Node TreeNode) {
    char * message = TreeNode.message;
    Node current = TreeNode;
    FILE * fileopen = fopen("graph.dot", "w");
    if(fileopen == NULL) return akinator_cannot_open_file;
    fprintf(fileopen, "digraph RoundedSplitGraph {\n");
    fprintf(fileopen, "rankdir=LR; \n");
    fprintf(fileopen, "node [shape=Mrecord, style=filled, fillcolor=\"#f9f9f9\", color=\"#2c3e50\", fontname=\"Arial\", fontsize=11];\n");




    fprintf(fileopen, "}\n");
    fclose(fileopen);
    return akinator_allright;
}
