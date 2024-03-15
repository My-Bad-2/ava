#include <stdlib.h>
#include <stddef.h>

int atoi(const char* nptr)
{
	return (int)strtol(nptr, (char**)NULL, 10);
}

long int atol(const char* nptr)
{
	return strtol(nptr, (char**)NULL, 10);
}

long long int atoll(const char* nptr)
{
	return strtoll(nptr, (char**)NULL, 10);
}