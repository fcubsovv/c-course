#include "../h/tricks.h"

int GetColorArray(uint32_t * num_array, const  char * target_image) {
    Image img = LoadImage(target_image);
    if (img.data == NULL) { printf("картинка не загрузилась\n"); return 1; }
    ImageResize(&img, 50, 50);
    Color * px = LoadImageColors(img);
    if (px == NULL) { printf("не получили пиксели\n"); return 1; }
    for (size_t i = 0; i < 2500; i++) {
        Color c = px[i];
        num_array[i] = (unsigned)c.r << 24 | (unsigned)c.g << 16 | (unsigned)c.b << 8 | (unsigned)c.a;
    }
    return 1;
}


int GetTargetFile(uint32_t * num_array, const char * filename) {

    FILE * file = fopen(filename, "w");
    fprintf(file, ";this file is auto generated. see c/tricks.cpp\n");
    for (size_t i = 0; i < 2500; i++) {
        fprintf(file, "PUSH %u\n", num_array[i]);
        fprintf(file, "POP [%zu]\n", i);
    }
    fprintf(file, "DRAW\n");
    fprintf(file, "HLT\n");
    fclose(file);
    return 0;
}


int CreateTargetFileForDrawingPic() {
    uint32_t arr[2500] = {};
    GetColorArray(arr, picture_file);
    GetTargetFile(arr, crypted_file);
    return 0;
}
