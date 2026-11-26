#include "../h/akinator-modes.h"


//__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

AKINATOR_TREE_ERRORS AkinatorPuts (const char * description, GAME_TYPE mode) {
    Font customFont = GetAkinatorFont();
    if (description == NULL) return null_ptr_to_line;
    Vector2 qTextSize = MeasureTextEx(customFont, description, 26, 1);
    Rectangle questionBox = { AKINATOR_BUTTON_RIGHT_POS, 50, AKINATOR_BUTTON_WIDTH, 100 };
    switch(mode) {
        case akinator_terminal_game:
            puts(description);
            return akinator_allright;
        case akinator_visual_game:
            DrawRectangleRounded((Rectangle){ questionBox.x + 4, questionBox.y + 4, questionBox.width, questionBox.height }, 0.25f, 12, Fade(BLACK, 0.3f));
            DrawRectangleRounded(questionBox, 0.25f, 12, akinator_parchmentBg);
            DrawRectangleRoundedLinesEx(questionBox, 0.25f, 12, 3.0f, akinator_borderBrown);
            DrawTextEx(
                customFont,
                description,
                (Vector2){ questionBox.x + (questionBox.width - qTextSize.x) / 2, questionBox.y + (questionBox.height - qTextSize.y) / 2 },
                26, 1, akinator_borderBrown
            );
            return akinator_allright;
        default:
            return invalid_game_type;
    }
    return invalid_game_type;
}


AKINATOR_TREE_ERRORS GetUserAnswer                  (char * line, GAME_TYPE mode) {
    if (mode == akinator_terminal_game) {
        scanf(" %127[^\n]", line);
        return akinator_allright;
    }
    else if (mode == akinator_visual_game) {
        //idk
        return akinator_allright;
    }

    return invalid_game_type;
}

//**************************************************************************************************************************************************************************************************************


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

static int GetTreeDebt                              (Node * TreeNode) {
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

static Node * FindCommonNode                        (Node * TreeNodeFirst, Node * TreeNodeSecond ) {
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

static AKINATOR_TREE_ERRORS FindOutCharacterInner   (Node * TreeNode, char * line, Node ** found_node, GAME_TYPE mode) {
    if (TreeNode == NULL) return null_ptr_to_node;

    AkinatorPuts(TreeNode->message, mode);
    if (TreeNode->left == NULL && TreeNode->right == NULL) {
        *found_node = TreeNode;
        return akinator_choose_mode;
    }

    GetUserAnswer(line, mode);

    if (strcmp(line, POSITIVE_ANS) == 0) {
        if (TreeNode->right) {
            FindOutCharacterInner(TreeNode->right, line, found_node, mode);
        }
        else {
            AkinatorPuts("no way from positive", mode);
            return null_ptr_to_node;
        }
    }
    else if (strcmp(line, NEGATIVE_ANS) == 0) {
        if (TreeNode->left) {
            FindOutCharacterInner(TreeNode->left, line, found_node, mode);
        }
        else {
            AkinatorPuts("no way from negative answer", mode);
            return null_ptr_to_node;
        }

    }
    else {
        AkinatorPuts("invalid answer", mode);
        return invalid_user_input;
    }

    return unexpected_behavior;
}

//*************************************************************************************************************************************************************************************************************************************


AKINATOR_TREE_ERRORS HandleDescribingCharacterMode  (Node * TreeNode, char * line, GAME_TYPE mode) {
    char * description = (char *) calloc (512, sizeof(char));
    GetUserAnswer(line, mode);
    Node * CurNode  = {};
    CurNode = InnerSearchOfCharacter(TreeNode, line);
    GetNodeDescription(TreeNode, CurNode, description);
    AkinatorPuts(description, mode);
    return akinator_choose_mode;
}

AKINATOR_TREE_ERRORS HandleAddCharacterMode         (Node * TreeNode, char * line, GAME_TYPE mode) {
    Node * leaf_node = NULL;
    FindOutCharacterInner(TreeNode, line, &leaf_node, mode);
    AkinatorPuts("is it correct?", mode);
    GetUserAnswer(line, mode);
    if(strcmp(line, NEGATIVE_ANS) == 0) {

        AkinatorPuts("do you want to add your character?", mode);
        GetUserAnswer(line, mode);
        if ( strcmp(line, NEGATIVE_ANS) == 0) return akinator_allright;
        else if (strcmp(line, POSITIVE_ANS) == 0) {
            AkinatorPuts("how feature for you character is true and for characher above is false", mode);
            GetUserAnswer(line, mode);
            Node * parent_node = leaf_node->parent;
                if (parent_node != NULL && parent_node->left == leaf_node) {

                    Node * NewNode = (Node *)calloc(1, sizeof(Node));


                    parent_node->left = NewNode;
                    NewNode->parent = parent_node;
                    snprintf( NewNode->message, sizeof( NewNode->message), "%s", line);
                    NewNode->identifier = HashString(NewNode->message);
                    NewNode->left = leaf_node;

                    AkinatorPuts("what is the name of your character", mode);
                    GetUserAnswer(line, mode);
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
                    AkinatorPuts("what is the name of your character", mode);
                    GetUserAnswer(line, mode);
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
                    AkinatorPuts("what is the name of your character", mode);
                    GetUserAnswer(line, mode);
                    Node * NewCharNode = (Node *)calloc(1, sizeof(Node));

                    snprintf( NewCharNode->message, sizeof( NewCharNode->message), "%s", line);
                    NewCharNode->identifier = HashString(NewCharNode->message);
                    NewCharNode->parent = NewNode;
                    NewNode->right = NewCharNode;
                    leaf_node->parent = NewNode;

                }
        } else {
            AkinatorPuts("invalid answer", mode);
            return akinator_allright;
        }


    }
    return akinator_choose_mode;
}

AKINATOR_TREE_ERRORS HandleCompareCharactersMode    (Node * TreeNode, char * line, GAME_TYPE mode) {

    AkinatorPuts("what is the name of the first character", mode);

    GetUserAnswer(line, mode);

    Node * CurNode1 = (Node *)calloc(1, sizeof(Node));
    CurNode1 = InnerSearchOfCharacter(TreeNode, line);
    if (CurNode1 == NULL) return null_ptr_to_node;

    AkinatorPuts("what is the name of the second character", mode);

    GetUserAnswer(line, mode);

    Node * CurNode2 = (Node *)calloc(1, sizeof(Node));
    CurNode2 = InnerSearchOfCharacter(TreeNode, line);

    if (CurNode2 == NULL) return null_ptr_to_node;

    CompareNodes(CurNode1, CurNode2, line);

    AkinatorPuts(line, mode);

    return akinator_choose_mode;
}

//________________________________________________________________________________________________________________________________________________________________________________________________________________________

AKINATOR_TREE_ERRORS HandleGameModes                (Node * TreeNode, AKINATOR_TREE_ERRORS MODE, GAME_TYPE mode) {

    char * answer = (char *) calloc (512, sizeof(char));
    AKINATOR_MODES_HANDLERS[MODE-1].handler(TreeNode, answer, mode);

    free(answer);

    return akinator_allright;
}
