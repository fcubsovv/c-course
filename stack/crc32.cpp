#ifndef CRC32
#define CRC32
#include <stdint.h>
#include <stddef.h>


uint32_t CalculateCRC32(const void *ptr, size_t size) {
    if (ptr == NULL || size == 0) return 0;

    const unsigned char *byte_ptr = (const unsigned char *)ptr;
    static uint32_t crc_table[256];
    static int is_table_initialized = 0;
    if (!is_table_initialized) {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t crc = i;
            for (uint32_t j = 0; j < 8; j++) {
                if (crc & 1) {
                    crc = (crc >> 1) ^ 0xEDB88320;
                } else {
                    crc >>= 1;
                }
            }
            crc_table[i] = crc;
        }
        is_table_initialized = 1;
    }
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < size; i++) {
        crc = (crc >> 8) ^ crc_table[(crc ^ byte_ptr[i]) & 0xFF];
    }

    return crc ^ 0xFFFFFFFF;
}
#endif
