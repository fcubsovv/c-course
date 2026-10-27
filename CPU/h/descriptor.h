#ifndef DESCRIPTOR
#define DESCRIPTOR
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "commands.h"
#include "../../global_utils/h/filework.h"

const char * const crypted_file   = "test-data/commands.txt";
const char * const decrypted_file = "test-data/execute.txt";

int ReadLinesFromBuffer(buffer_struct buffer);

int Descript(void) ;



#endif
