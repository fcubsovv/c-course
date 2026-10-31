#ifndef HELPERS_SPU
#define HELPERS_SPU
#include <stdio.h>
#include "raylib.h"
#include "../../global_utils/h/filework.h"

size_t count_lines_helper(buffer_struct read);

int CreateTargetFile();
int GetColorArray(uint32_t * num_array,const  char * target_image);
int GetTargetFile(uint32_t * num_array, const char * filename);
#endif
