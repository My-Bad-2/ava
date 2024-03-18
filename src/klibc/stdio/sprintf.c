#include "local.h"

int vsprintf(char* buffer, const char* format, va_list args)
{
	return vsnprintf(buffer, STDIO_MAX_BUFFER_SIZE, format, args);
}

int sprintf(char* buffer, const char* format, ...)
{
	va_list args;

	va_start(args, format);
	const int ret = vsprintf(buffer, format, args);
	va_end(args);

	return ret;
}