#include <stdlib.h>
#include <inttypes.h>

long long strtoll(const char* restrict nptr, char** restrict endptr, int base)
{
	return strtoimax(nptr, endptr, base);
}

unsigned long long strtoull(const char* restrict nptr, char** restrict endptr, int base)
{
	return (unsigned long long)strtoumax(nptr, endptr, base);
}