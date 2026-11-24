#ifndef AKINATOR_MODES
#define AKINATOR_MODES
#include "tree_declaration.h"
#include <stdio.h>
#define POSITIVE_ANS "+"
#define NEGATIVE_ANS "-"
#include "helpers.h"

enum AKINATOR_GAME_MODES {
    akinator_idle                   = 0,
    akinator_findout_add_character  = 1,
    akinator_describe_character     = 2,
    akinator_compare_character      = 3,
};

AKINATOR_TREE_ERRORS HandleDescribingCharacterMode  (Node * TreeNode, char * line);
AKINATOR_TREE_ERRORS HandleAddCharacterMode         (Node * TreeNode, char * line);
AKINATOR_TREE_ERRORS HandleCompareCharactersMode    (Node * TreeNode, char * line);

struct AkinatorGameMode {
    AKINATOR_TREE_ERRORS (*handler) (Node * TreeNode, char * line);
    AKINATOR_GAME_MODES mode_code;
};

const AkinatorGameMode AKINATOR_MODES_HANDLERS[] = {
    { HandleAddCharacterMode,        akinator_findout_add_character },
    { HandleDescribingCharacterMode, akinator_describe_character    },
    { HandleCompareCharactersMode,   akinator_compare_character     }
};


AKINATOR_TREE_ERRORS HandleGameModes(Node * TreeNode, AKINATOR_GAME_MODES MODE);




#endif
