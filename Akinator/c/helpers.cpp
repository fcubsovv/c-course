#include "../h/helpers.h"

uint64_t HashString(const char *str) {
    uint64_t hash = 5381;
    int c = 0;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}
