#include "../h/helpers.h"


size_t count_lines_helper(buffer_struct read) {
    size_t lines = 0;
    for (size_t i = 0; i < read.nitems; i++) {
        if (read.buffer[i] == '\n') {
            lines ++;
        }
    }
    return lines;
}

int GetColorArray(uint32_t * num_array,const  char * target_image) {
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
    for (size_t i = 0; i < 2500; i++) {
        fprintf(file, "PUSH %u\n", num_array[i]);
        fprintf(file, "POP [%zu]\n", i);
    }
    fprintf(file, "DRAW\n");
    fprintf(file, "HLT\n");
    fclose(file);
    return 0;
}



