#include "local.h"
#include <stdio.h>

int vfprintf(FILE* fp, const char* format, va_list args)
{
	return stdio_vsnprintf(fp, format, args);
}

int vprintf(const char* format, va_list args)
{
	return vfprintf(stdout, format, args);
}