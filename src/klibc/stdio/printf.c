#include <stdio.h>

int fprintf(FILE* fp, const char* format, ...)
{
	va_list args;

	va_start(args, format);
	const int ret = vfprintf(fp, format, args);
	va_end(args);

	return ret;
}

int printf(const char* format, ...)
{
	va_list args;

	va_start(args, format);
	const int ret = vprintf(format, args);
	va_end(args);

	return ret;
}