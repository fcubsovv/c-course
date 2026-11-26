#ifndef AKINATOR_PAINTER_
#define AKINATOR_PAINTER_
#include "raylib.h"

#define AKINATOR_SCREEN_WIDTH 1000
#define AKINATOR_SCREEN_HEIGHT 600

#define AKINATOR_BUTTON_WIDTH 320.0f
#define AKINATOR_BUTTON_HEIGHT 65.0f
#define AKINATOR_BUTTON_RIGHT_POS 600.0f
#define AKINATOR_BUTTON_UP_POS 180.0f
#define AKINATOR_BUTTON_SPACE 85.0f

const char * const akinator_bg_filename  = "bg.png";
const char * const akinator_pic_filename = "akinator.png";

const Color akinator_goldTop      = (Color){ 255, 223, 115, 255 };
const Color akinator_goldBottom   = (Color){ 230, 150,  30, 255 };
const Color akinator_hoverTop     = (Color){ 255, 240, 160, 255 };
const Color akinator_hoverBottom  = (Color){ 245, 175,  50, 255 };
const Color akinator_borderBrown  = (Color){  92,  50,  15, 255 };
const Color akinator_parchmentBg  = (Color){ 255, 248, 225, 235 };

Font GetAkinatorFont();

#endif
