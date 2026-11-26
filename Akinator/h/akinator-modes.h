#ifndef AKINATOR_MODES
#define AKINATOR_MODES
#include "tree_declaration.h"
#include "../h/akinator_painter.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#define POSITIVE_ANS "+"
#define NEGATIVE_ANS "-"
#include "helpers.h"

enum GAME_TYPE {
    akinator_terminal_game  = 1,
    akinator_visual_game    = 2,
};


AKINATOR_TREE_ERRORS HandleDescribingCharacterMode  (Node * TreeNode, char * line, GAME_TYPE mode);
AKINATOR_TREE_ERRORS HandleAddCharacterMode         (Node * TreeNode, char * line, GAME_TYPE mode);
AKINATOR_TREE_ERRORS HandleCompareCharactersMode    (Node * TreeNode, char * line, GAME_TYPE mode);

AKINATOR_TREE_ERRORS HandleGameModes                (Node * TreeNode, AKINATOR_TREE_ERRORS MODE, GAME_TYPE mode);


struct AkinatorGameMode {
    AKINATOR_TREE_ERRORS (*handler) (Node * TreeNode, char * line, GAME_TYPE mode);
    AKINATOR_TREE_ERRORS mode_code;
};


const AkinatorGameMode AKINATOR_MODES_HANDLERS[] = {
    { HandleAddCharacterMode,        akinator_findout_add_character },
    { HandleDescribingCharacterMode, akinator_describe_character    },
    { HandleCompareCharactersMode,   akinator_compare_character     }
};

AKINATOR_TREE_ERRORS GetUserAnswer                  (char * line, GAME_TYPE mode) ;

AKINATOR_TREE_ERRORS AkinatorPuts                   (const char * description, GAME_TYPE mode);

#endif
