#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUFSIZE 1024

typedef struct __file {
	char* buffer;
	size_t position;
	size_t max_chars;

	void* extra_arg;
	void (*write)(int c, void* extra_arg);
} FILE;

extern FILE __streams[];

#define stdin (&__streams[0])
#define stdout (&__streams[1])
#define stderr (&__streams[2])

int fputc(int ch, FILE* fp);
int fputs(const char* restrict str, FILE* fp);

int putc(int ch, FILE* fp);
int putchar(int ch);
int puts(const char* restrict str);

int fprintf(FILE* fp, const char* format, ...) __PRINTFLIKE(2, 3);
int vfprintf(FILE* fp, const char* format, va_list args) __PRINTFLIKE(2, 0);

int printf(const char* format, ...) __PRINTFLIKE(1, 2);
int vprintf(const char* format, va_list args) __PRINTFLIKE(1, 0);

int sprintf(char* buffer, const char* format, ...) __PRINTFLIKE(2, 3);
int vsprintf(char* buffer, const char* format, va_list args) __PRINTFLIKE(2, 0);

int snprintf(char* buffer, size_t n, const char* format, ...)
	__PRINTFLIKE(3, 4);
int vsnprintf(char* buffer, size_t n, const char* format, va_list args)
	__PRINTFLIKE(3, 0);

#ifdef __cplusplus
}
#endif

#endif	// _STDIO_H