#include <stdint.h>
#include <string.h>

int memcmp(const void* s1, const void* s2, size_t n) {
    register const uint8_t* str1 = s1;
    register const uint8_t* str2 = s2;

    if (n == 0) {
        return 0;
    }

    do {
        if (*str1++ != *str2++) {
            return *--str1 - *--str2;
        }
    } while (--n != 0);

    return 0;
}
