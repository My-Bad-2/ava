#include <stdio.h>
#include <string.h>
#include <sys/errors.h>

int fputs(const char *restrict str, FILE *fp) {
    const size_t length = strlen(str);

    for(size_t i = 0; i < length; ++i) {
        int ret = fputc(str[i], fp);

        if(ret != SUCCESS) {
            return ret;
        }
    }

    return SUCCESS;
}

int puts(const char *restrict str) {
    return fputs(str, stdout);
}
