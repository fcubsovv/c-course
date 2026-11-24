#include "../h/akinator-modes.h"
#include <cstdlib>
#include <cstring>

static AKINATOR_TREE_ERRORS GetUserAnswer           (char * line) {
    scanf(" %127[^\n]", line);
    return akinator_allright;
}

static Node * InnerSearchOfCharacter                (Node * TreeNode, char * character) {
    if (TreeNode->left == NULL && TreeNode->right == NULL) {
        return strcmp(TreeNode->message, character) == 0 ? TreeNode : NULL;
    }
    Node * posNode = {};
    if (TreeNode->right) {
        posNode = InnerSearchOfCharacter(TreeNode->right, character);
        if (posNode != NULL) {
            return posNode;
        }
    }
    if (TreeNode->left) {
        return InnerSearchOfCharacter(TreeNode->left, character);
    }
    return NULL;
}

static int GetTreeDebt (Node * TreeNode) {
    int depth = 0;
    while (TreeNode->parent != NULL) { TreeNode = TreeNode->parent; depth++; }
    return depth;
}

static AKINATOR_TREE_ERRORS GetNodeDescription      (Node * RootNode, Node * TreeNode, char * description) {
    if (TreeNode == NULL) return null_ptr_to_node;
    if (RootNode == TreeNode) return akinator_allright;

    Node * Parent = TreeNode->parent;
    if (Parent == NULL) return unexpected_behavior;


    if (Parent->left == TreeNode) strcat(description, "NOT ");
    strcat(description, Parent->message);
    strcat(description, ", ");

    return GetNodeDescription(RootNode, Parent, description);
}

static Node * FindCommonNode ( Node * TreeNodeFirst, Node * TreeNodeSecond ) {
    if (TreeNodeFirst == NULL) return NULL;
    if (TreeNodeSecond == NULL) return NULL;

    int dep1h = GetTreeDebt(TreeNodeFirst);
    int dep2h = GetTreeDebt(TreeNodeSecond);

    while (dep1h > dep2h) { TreeNodeFirst  = TreeNodeFirst->parent;  dep1h--;  }
    while (dep2h > dep1h) { TreeNodeSecond  = TreeNodeSecond->parent;  dep2h--;  }


    while (TreeNodeFirst != TreeNodeSecond) {
        if (TreeNodeFirst->parent == NULL) return NULL;
        if (TreeNodeSecond->parent == NULL) return NULL;
        TreeNodeFirst  = TreeNodeFirst->parent;
        TreeNodeSecond = TreeNodeSecond->parent;
    }
    return TreeNodeFirst;
}

static AKINATOR_TREE_ERRORS CompareNodesInner       (Node * TreeNodeFirst, Node * TreeNodeSecond, char * comparison_message_first, char * comparison_message_second) {

    Node * CommonNode = FindCommonNode(TreeNodeFirst, TreeNodeSecond);
    GetNodeDescription(CommonNode, TreeNodeFirst, comparison_message_first);
    GetNodeDescription(CommonNode, TreeNodeSecond, comparison_message_second);


    return akinator_allright;
}

static AKINATOR_TREE_ERRORS CompareNodes            (Node * TreeNodeFirst, Node * TreeNodeSecond, char * comparison_message) {

    char * comparison_message_first = (char *)calloc(256, sizeof(char));
    char * comparison_message_second = (char *)calloc(256, sizeof(char));

    CompareNodesInner(TreeNodeFirst, TreeNodeSecond, comparison_message_first, comparison_message_second);

    strcat(comparison_message, "The first is : ");
    strcat(comparison_message, comparison_message_first);
    strcat(comparison_message, "\n");

    strcat(comparison_message, "While the second is : ");
    strcat(comparison_message, comparison_message_second);
    strcat(comparison_message, "\n");

    return akinator_allright;
}

static AKINATOR_TREE_ERRORS FindOutCharacterInner   (Node * TreeNode, char * line, Node ** found_node) {
    if (TreeNode == NULL) return null_ptr_to_node;

    puts(TreeNode->message);
    if (TreeNode->left == NULL && TreeNode->right == NULL) {
        *found_node = TreeNode;
        return choose_game_mode;
    }

    GetUserAnswer(line);

    if (strcmp(line, POSITIVE_ANS) == 0) {
        if (TreeNode->right) {
            FindOutCharacterInner(TreeNode->right, line, found_node);
        }
        else {
            puts("no way from positive");
            return null_ptr_to_node;
        }
    }
    else if (strcmp(line, NEGATIVE_ANS) == 0) {
        if (TreeNode->left) {
            FindOutCharacterInner(TreeNode->left, line, found_node);
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

//________________________________________________________________________________________________________________________________________________________

AKINATOR_TREE_ERRORS HandleDescribingCharacterMode  (Node * TreeNode, char * line) {
    char * description = (char *) calloc (512, sizeof(char));
    GetUserAnswer(line);
    Node * CurNode  = {};
    CurNode = InnerSearchOfCharacter(TreeNode, line);
    GetNodeDescription(TreeNode, CurNode, description);
    puts(description);
    return unexpected_behavior;
}

AKINATOR_TREE_ERRORS HandleAddCharacterMode         (Node * TreeNode, char * line) {
    Node * leaf_node = NULL;
    FindOutCharacterInner(TreeNode, line, &leaf_node);
    puts("is it correct?");
    GetUserAnswer(line);
    if(strcmp(line, NEGATIVE_ANS) == 0) {

        puts("do you want to add your character?");
        GetUserAnswer(line);
        if ( strcmp(line, NEGATIVE_ANS) == 0) return akinator_allright;
        else if (strcmp(line, POSITIVE_ANS) == 0) {
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
        } else {
            puts("invalid answer");
            return akinator_allright;
        }


    }
    return akinator_allright;
}

AKINATOR_TREE_ERRORS HandleCompareCharactersMode    (Node * TreeNode, char * line) {

    puts("what is the name of the first character");
    GetUserAnswer(line);
    Node * CurNode1 = (Node *)calloc(1, sizeof(Node));
    CurNode1 = InnerSearchOfCharacter(TreeNode, line);
    if (CurNode1 == NULL) return null_ptr_to_node;
    puts("what is the name of the second character");
    GetUserAnswer(line);
    Node * CurNode2 = (Node *)calloc(1, sizeof(Node));
    CurNode2 = InnerSearchOfCharacter(TreeNode, line);
    if (CurNode2 == NULL) return null_ptr_to_node;
    CompareNodes(CurNode1, CurNode2, line);
    puts(line);

    return akinator_allright;
}

AKINATOR_TREE_ERRORS HandleGameModes(Node * TreeNode, AKINATOR_GAME_MODES MODE) {

    char * answer = (char *) calloc (512, sizeof(char));
    AKINATOR_MODES_HANDLERS[MODE-1].handler(TreeNode, answer);

    return akinator_allright;
}
