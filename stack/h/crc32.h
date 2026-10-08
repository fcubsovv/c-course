#ifndef CRC32
#define CRC32
#include <stdint.h>
#include <stddef.h>

//see https://gist.github.com/xobs/91a84d29152161e973d717b9be84c4d0

uint32_t CalculateCRC32(const void *ptr, size_t size) ;

#endif
