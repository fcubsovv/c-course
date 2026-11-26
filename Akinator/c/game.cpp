#include "../h/game.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define PUTS_GAME_HEADER    puts("****************************************************");\
                            puts("*******************AKINATOR GAME!*******************"); \
                            puts("****************************************************");

#define PUTS_CHOOSE_MODE    puts("###############--CHOOSE GAME REGIME--###############");
#define PUTS_GAME_MODES     puts("------------------ GAME MODES ----------------------"); \
                            puts("---> [1] Findout character & add new character");\
                            puts("---> [2] Describe character");\
                            puts("---> [3] Compare characters"); \
                            puts("---> [4] End");
#define END_AKINATOR_GAME   puts("****************************************************");\
                            puts("*******************AKINATOR END!********************"); \
                            puts("****************************************************");
#define RULES               puts("------------------ USER ANSWERS --------------------"); \
                            puts("---> [+] Positive answer");   \
                            puts("---> [-] Negative answer");   \
                            puts("---> [character name] Character name");




AKINATOR_TREE_ERRORS PutsAkinatorChooseMode (GAME_TYPE mode) {
    switch(mode) {
        case akinator_terminal_game:
            PUTS_CHOOSE_MODE
            return akinator_allright;
        case akinator_visual_game:
            AkinatorPuts("Выбери тип игры",mode);
            return akinator_allright;
        default:
            return invalid_game_type;
    }
    return invalid_game_type;
}
AKINATOR_TREE_ERRORS PutsAkinatorGameModes  (GAME_TYPE mode) {
    switch(mode) {
        case akinator_terminal_game:
            PUTS_GAME_MODES
            return akinator_allright;
        case akinator_visual_game:
            //buttons for game modes
            return akinator_allright;
        default:
            return invalid_game_type;
    }
    return invalid_game_type;
}
AKINATOR_TREE_ERRORS PutsGameHeader         (GAME_TYPE mode) {
    switch(mode) {
        case akinator_terminal_game:
            PUTS_GAME_HEADER
            return akinator_allright;
        case akinator_visual_game:
            AkinatorPuts("Давай я угадаю!", mode);
            return akinator_allright;
        default:
            return invalid_game_type;
    }
    return invalid_game_type;
}
AKINATOR_TREE_ERRORS PutsGameRules          (GAME_TYPE mode) {
    switch(mode) {
        case akinator_terminal_game:
            RULES
            return akinator_allright;
        case akinator_visual_game:
            AkinatorPuts("Сейчас я расскажу тебе правила игры!", mode);
            sleep(2);
            AkinatorPuts("Выбирай Да - если утверждение про твоего героя, Нет - если нет!", mode);
            sleep(2);
            AkinatorPuts("Если нужно ввести имя вводи точно до регистра и пробела в конце!", mode);
            return akinator_allright;
        default:
            return invalid_game_type;
    }
    return invalid_game_type;
}
AKINATOR_TREE_ERRORS PutsGameEnd            (GAME_TYPE mode) {
    switch(mode) {
        case akinator_terminal_game:
            END_AKINATOR_GAME
            return akinator_allright;
        case akinator_visual_game:
            AkinatorPuts("Конец игры!", mode);
            return akinator_allright;
        default:
            return invalid_game_type;
    }
    return invalid_game_type;
}

AKINATOR_TREE_ERRORS InitAkinatorWindow() {
    InitWindow(AKINATOR_SCREEN_WIDTH, AKINATOR_SCREEN_HEIGHT, "Akinator Game");
    SetTargetFPS(60);

    Texture2D bgTexture = LoadTexture(akinator_bg_filename);
    Texture2D akinatorTexture = LoadTexture(akinator_pic_filename);

    return akinator_allright;
};


AKINATOR_TREE_ERRORS PlayAkinatorGameTerminal (Node * TreeNode, GAME_TYPE mode) {

    char * line = (char*)calloc(256, sizeof(char));
    if (line == NULL) return error_allocating_memory;

    if (mode > akinator_visual_game || mode < akinator_terminal_game) return invalid_game_type;
    InitAkinatorWindow();
    PutsGameHeader(mode);
    PutsAkinatorGameModes(mode);
    PutsGameRules(mode);

    AKINATOR_TREE_ERRORS state = akinator_choose_mode;

    while(state != akinator_end && state >= 0 && (mode == akinator_visual_game ? !WindowShouldClose() : 1)) {
        switch(state) {
            case akinator_choose_mode:
                PutsAkinatorChooseMode(mode);
                PutsAkinatorGameModes(mode);
                GetUserAnswer(line, mode);
                if (strcmp("1", line) == 0){ state = akinator_findout_add_character; break;}
                else if (strcmp("2", line) == 0){ state = akinator_describe_character; break;}
                else if (strcmp("3", line) == 0){ state = akinator_compare_character; break;}
                else if (strcmp("4", line) == 0){ state = akinator_end; break;}
                else AkinatorPuts("invalid mode", mode); state = akinator_choose_mode;
            default:
                AKINATOR_TREE_ERRORS substate = HandleGameModes(TreeNode, state, mode);
                AkinatorPuts("CONTINUE?", mode);
                GetUserAnswer(line, mode);
                if (strcmp(line, POSITIVE_ANS) == 0) {continue;}
                else if (strcmp(line, NEGATIVE_ANS) == 0) {state = substate;}
                else {
                    AkinatorPuts("invalid input", mode);
                    state = substate;
                }
        }

    }
    PutsGameEnd(mode);
    return state;

};

