#include <string.h>

char* strcat(char* restrict dest, const char* restrict src) {
    const size_t dest_len = strlen(dest);
    const size_t src_len = strlen(src);

    memcpy(dest + dest_len, src, src_len);
    dest[dest_len + src_len] = '\0';

    return dest;
}

char* strncat(char* restrict dest, const char* restrict src, size_t maxlen) {
    const size_t dest_len = strlen(dest);
    const size_t src_len = strnlen(src, maxlen);

    const size_t copy_len = src_len < maxlen ? src_len : maxlen;

    memcpy(dest + dest_len, src, copy_len);
    dest[dest_len + copy_len] = '\0';

    return dest;
}
