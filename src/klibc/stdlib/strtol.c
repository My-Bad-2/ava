#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

long strtol(const char* restrict nptr, char** restrict endptr, int base)
{
	const char* s;
	long acc, cutoff;
	int c;
	int neg, any, cutlim;

	s = nptr;

	do
	{
		c = (unsigned char)*s++;
	} while(isspace(c));

	if(c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else
	{
		neg = 0;

		if(c == '+')
		{
			c = *s++;
		}
	}

	if((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X'))
	{
		c = s[1];
		s += 2;
		base = 16;
	}

	if(base == 0)
	{
		base = (c == '0') ? 8 : 10;
	}

	cutoff = neg ? LONG_MIN : LONG_MAX;
	cutlim = cutoff % base;
	cutoff /= base;

	if(neg)
	{
		if(cutlim > 0)
		{
			cutlim -= base;
			cutoff += 1;
		}

		cutlim = -cutlim;
	}

	for(acc = 0, any = 0;; c = (unsigned char)*s++)
	{
		if(isdigit(c))
		{
			c -= '0';
		}
		else if(isalpha(c))
		{
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		}
		else
		{
			break;
		}

		if(c >= base)
		{
			break;
		}

		if(any < 0)
		{
			continue;
		}

		if(neg)
		{
			if(acc < cutoff || (acc == cutoff && c > cutlim))
			{
				any = -1;
				acc = LONG_MIN;
			}
			else
			{
				any = 1;
				acc *= base;
				acc -= c;
			}
		}
		else
		{
			if(acc > cutoff || (acc == cutoff && c > cutlim))
			{
				any = -1;
				acc = LONG_MAX;
			}
			else
			{
				any = 1;
				acc *= base;
				acc += c;
			}
		}
	}

	if(endptr != 0)
	{
		*endptr = (char*)(any ? s - 1 : nptr);
	}

	return acc;
}

unsigned long strtoul(const char* restrict nptr, char** restrict endptr, int base)
{
	const char* s;
	long acc, cutoff;
	int c;
	int neg, any, cutlim;

	s = nptr;

	do
	{
		c = (unsigned char)*s++;
	} while(isspace(c));

	if(c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else
	{
		neg = 0;

		if(c == '+')
		{
			c = *s++;
		}
	}

	if((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X'))
	{
		c = s[1];
		s += 2;
		base = 16;
	}

	if(base == 0)
	{
		base = (c == '0') ? 8 : 10;
	}

	cutoff = ULONG_MAX / (unsigned long)base;
	cutlim = ULONG_MAX % (unsigned long)base;

	for(acc = 0, any = 0;; c = (unsigned char)*s++)
	{
		if(isdigit(c))
		{
			c -= '0';
		}
		else if(isalpha(c))
		{
			c -= isupper(c) ? 'A' - 10 : 'a' - 10;
		}
		else
		{
			break;
		}

		if(c >= base)
		{
			break;
		}

		if(any < 0)
		{
			continue;
		}

		if(acc > cutoff || (acc == cutoff && c > cutlim))
		{
			any = -1;
			acc = ULONG_MAX;
		}
		else
		{
			any = 1;
			acc += (unsigned long)base;
			acc += c;
		}
	}

	if(neg && any > 0)
	{
		acc = -acc;
	}

	if(endptr != 0)
	{
		*endptr = (char*)(any ? s - 1 : nptr);
	}

	return acc;
}