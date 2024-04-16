#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

int memcmp(const void* s1, const void* s2, size_t n);
void* memset(void* dest, int c, size_t n);
void* memcpy(void* restrict dest, const void* restrict src, size_t n);
void* memmove(void* dest, const void* src, size_t n);

size_t strlen(const char* str);
size_t strnlen(const char* str, size_t max_len);

char* strcpy(char* restrict dest, const char* restrict src);
char* strncpy(char* restrict dest, const char* restrict src, size_t max_len);

int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);

char* strcat(char* restrict dst, const char* restrict src);
char* strncat(char* restrict dst, const char* restrict src, size_t maxlen);

__END_DECLS

#endif  // _STRING_H
