#include "../h/akinator_painter.h"



Font GetAkinatorFont() {

    int codepoints[512] = { 0 };
    int count = 0;
    for (int i = 32; i <= 126; i++) codepoints[count++] = i;
    for (int i = 1024; i <= 1105; i++) codepoints[count++] = i;

    Font customFont = LoadFontEx("font.ttf", 36, codepoints, count);
    SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);
    return customFont;
}


