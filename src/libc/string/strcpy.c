#include <string.h>

char* strcpy(char* restrict dest, const char* restrict src) {
    const size_t length = strlen(src);

    memcpy(dest, src, length + 1);

    return dest;
}

char* strncpy(char* restrict dest, const char* restrict src, size_t maxlen) {
    const size_t src_len = strnlen(src, maxlen);

    if (src_len < maxlen) {
        memcpy(dest, src, src_len);
        memset(dest + src_len, 0, maxlen - src_len);
    } else {
        memcpy(dest, src, maxlen);
    }

    return dest;
}
