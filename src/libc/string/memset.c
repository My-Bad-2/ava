#include <stdint.h>
#include <string.h>

void* memset(void* dest, register int c, register size_t n) {
    if (dest == NULL) {
        return NULL;
    }

    register uint8_t* ptr = dest;

    while (n-- > 0) {
        *ptr++ = c;
    }

    return dest;
}
