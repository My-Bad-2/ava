#ifndef KLIBC_INCLUDE_STDLIB_H
#define KLIBC_INCLUDE_STDLIB_H

#include <sys/features.h>

__BEGIN_DECLS

typedef struct
{
	int quot;
	int rem;
} div_t;

typedef struct
{
	long int quot;
	long int rem;
} ldiv_t;

typedef struct
{
	long long int quot;
	long long int rem;
} lldiv_t;

int atoi(const char* nptr) __NONNULL((1));
long int atol(const char* nptr) __NONNULL((1));
long long int atoll(const char* nptr) __PURE __NONNULL((1));

long int strtol(const char* restrict nptr, char** restrict endptr, int base) __NONNULL((1));
unsigned long int strtoul(const char* restrict nptr, char** restrict endptr, int base)
	__NONNULL((1));

long long int strtoll(const char* restrict nptr, char** restrict endptr, int base) __NONNULL((1));
unsigned long long int strtoull(const char* restrict nptr, char** restrict endptr, int base)
	__NONNULL((1));

int abs(int x) __CONST;
long labs(long x) __CONST;
long long llabs(long long x) __CONST;

div_t div(int numer, int denom) __CONST;
ldiv_t ldiv(long numer, long denom) __CONST;
lldiv_t lldiv(long long numer, long long denom) __CONST;

__END_DECLS

#endif // KLIBC_INCLUDE_STDLIB_H