#include "../h/tree-dumpers.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>

AKINATOR_TREE_ERRORS PrintTree (Node * TreeNode) {

    if (!TreeNode) return null_ptr_to_node;

        puts(TreeNode->message);

    if (TreeNode->left) {
        PrintTree(TreeNode->left);
    }
    if (TreeNode->right) {
        PrintTree(TreeNode->right);
    }

    return tree_allright;
}

static AKINATOR_TREE_ERRORS fPrintfNode(Node * TreeNode, FILE *fileopen) {
    if (TreeNode == NULL || fileopen == NULL) return null_ptr_to_node;


    fprintf(fileopen, "Node%llu [label=\"{ %s | { <left> no | <right> yes } | id: %llu }\"];\n",
            TreeNode->identifier, TreeNode->message, TreeNode->identifier);


    if (TreeNode->left) {
        fprintf(fileopen, "Node%llu:left -> Node%llu [color=blue];\n",
                TreeNode->identifier, TreeNode->left->identifier);
        fPrintfNode(TreeNode->left, fileopen);
    }
    if (TreeNode->right) {
        fprintf(fileopen, "Node%llu:right -> Node%llu [color=green];\n",
                TreeNode->identifier, TreeNode->right->identifier);
        fPrintfNode(TreeNode->right, fileopen);
    }


    if (TreeNode->parent) {
        fprintf(fileopen, "Node%llu -> Node%llu [color=red, style=dashed];\n",
                TreeNode->identifier, TreeNode->parent->identifier);
    }

    return tree_allright;
}


AKINATOR_TREE_ERRORS CreateTreeGraph (Node * TreeNode) {
    if (TreeNode == NULL) return null_ptr_to_node;
    const char * message = TreeNode->message;
    FILE * fileopen = fopen("graph.dot", "w");
    if(fileopen == NULL) return akinator_cannot_open_file;
    fprintf(fileopen, "digraph RoundedSplitGraph {\n");
    fprintf(fileopen, "rankdir=TB;\n");
    fprintf(fileopen, "node [shape=Mrecord, style=filled, fillcolor=\"#f9f9f9\", color=\"#2c3e50\", fontname=\"Arial\", fontsize=11];\n");

    fPrintfNode(TreeNode, fileopen);

    fprintf(fileopen, "}\n");
    fclose(fileopen);
    const char * command2 = "dot -Tpng graph.dot -o graph.png";
    int status2 = system(command2);
    return tree_allright;
}
