#include "../h/akinator-modes.h"
#include <cstdlib>
#include <cstring>

static AKINATOR_TREE_ERRORS GetUserAnswer(char * line) {
    scanf("%127s", line);
    return akinator_allright;
}

static const char * InnerSearchOfCharacter(Node * TreeNode, char * description, char * character) {
    if (strcmp(TreeNode->message, character) == 0) {
        return description;
    }
    strcat(description, TreeNode->message);
    if (TreeNode->right) {
        InnerSearchOfCharacter(TreeNode->right, description, character);
    }
    if (TreeNode->left) {
        InnerSearchOfCharacter(TreeNode->left, description, character);
    }

    return "error-description";
}

//________________________________________________________________________________________________________________________________________________________

AKINATOR_TREE_ERRORS HandleFindOutCharacterMode(Node * TreeNode, char * line, Node ** found_node) {
    if (TreeNode == NULL) return null_ptr_to_node;

    puts(TreeNode->message);
    if (TreeNode->left == NULL && TreeNode->right == NULL) {
        *found_node = TreeNode;
        return choose_game_mode;
    }

    GetUserAnswer(line);

    if (strcmp(line, POSITIVE_ANS) == 0) {
        if (TreeNode->right) {
            HandleFindOutCharacterMode(TreeNode->right, line, found_node);
        }
        else {
            puts("no way from positive");
            return null_ptr_to_node;
        }
    }
    else if (strcmp(line, NEGATIVE_ANS) == 0) {
        if (TreeNode->left) {
            HandleFindOutCharacterMode(TreeNode->left, line, found_node);
        }
        else {
            puts("no way from negative answer");
            return null_ptr_to_node;
        }

    }
    else {
        puts("invalid answer");
        return invalid_user_input;
    }

    return unexpected_behavior;
}

AKINATOR_TREE_ERRORS HandleDescribingCharacterMode(Node * TreeNode, char * line) {
    char * description = (char *) calloc (512, sizeof(char));
    GetUserAnswer(line);
    InnerSearchOfCharacter(TreeNode, description, line);
    puts(description);
    return unexpected_behavior;
}

AKINATOR_TREE_ERRORS HandleAddCharacterMode (Node * TreeNode, char * line) {
    Node * leaf_node = NULL;
    HandleFindOutCharacterMode(TreeNode, line, &leaf_node);
    puts("is it correct?");
    GetUserAnswer(line);
    if(strcmp(line, NEGATIVE_ANS) == 0) {
        puts("how feature for you character is true and for characher above is false");
        GetUserAnswer(line);
        Node * parent_node = leaf_node->parent;
            if (parent_node != NULL && parent_node->left == leaf_node) {

                Node * NewNode = (Node *)calloc(1, sizeof(Node));


                parent_node->left = NewNode;
                NewNode->parent = parent_node;
                snprintf( NewNode->message, sizeof( NewNode->message), "%s", line);
                NewNode->identifier = HashString(NewNode->message);
                NewNode->left = leaf_node;

                puts("what is the name of your character");
                GetUserAnswer(line);
                Node * NewCharNode = (Node *)calloc(1, sizeof(Node));

                snprintf( NewCharNode->message, sizeof( NewCharNode->message), "%s", line);
                NewCharNode->identifier = HashString(NewCharNode->message);
                NewNode->right = NewCharNode;
                NewCharNode->parent = NewNode;
                leaf_node->parent = NewNode;

            } else if (leaf_node->parent != NULL && leaf_node->parent->right == leaf_node) {
                Node * NewNode = (Node *)calloc(1, sizeof(Node));

                NewNode->parent = leaf_node->parent;
                snprintf( NewNode->message, sizeof( NewNode->message), "%s", line);
                NewNode->identifier = HashString(NewNode->message);
                NewNode->left = leaf_node;
                puts("what is the name of your character");
                GetUserAnswer(line);
                Node * NewCharNode = (Node *)calloc(1, sizeof(Node));

                snprintf( NewCharNode->message, sizeof( NewCharNode->message), "%s", line);
                NewCharNode->identifier = HashString(NewCharNode->message);
                NewCharNode->parent = NewNode;
                NewNode->right = NewCharNode;
                leaf_node->parent->right = NewNode;
                leaf_node->parent = NewNode;
            } else {
                Node * NewNode = (Node *)calloc(1, sizeof(Node));

                NewNode->parent = leaf_node->parent;
                snprintf( NewNode->message, sizeof( NewNode->message), "%s", line);
                NewNode->identifier = HashString(NewNode->message);
                NewNode->left = leaf_node;
                puts("what is the name of your character");
                GetUserAnswer(line);
                Node * NewCharNode = (Node *)calloc(1, sizeof(Node));

                snprintf( NewCharNode->message, sizeof( NewCharNode->message), "%s", line);
                NewCharNode->identifier = HashString(NewCharNode->message);
                NewCharNode->parent = NewNode;
                NewNode->right = NewCharNode;
                leaf_node->parent = NewNode;

            }


    }
    return akinator_allright;
}

AKINATOR_TREE_ERRORS HandleGameModes(Node * TreeNode) {

    char * answer = (char *) calloc (128, sizeof(char));


    return akinator_allright;
}
