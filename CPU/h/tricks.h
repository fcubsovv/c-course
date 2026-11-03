#ifndef TRICKS
#define TRICKS
#include <stdio.h>
#include "raylib.h"
#include <stdint.h>
#include "_FILES_.h"

int GetColorArray(uint32_t * num_array, const  char * target_image);
int GetTargetFile(uint32_t * num_array, const char * filename);
int CreateTargetFileForDrawingPic();


#endif
