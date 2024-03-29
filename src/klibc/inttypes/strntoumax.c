#include <inttypes.h>
#include <ctype.h>

static inline int strntoumax_digitval(int c)
{
	unsigned d;

	d = (unsigned)(c - '0');

	if(d < 10)
	{
		return (int)d;
	}

	d = (unsigned)(c - 'a');

	if(d < 6)
	{
		return (int)(d + 10);
	}

	d = (unsigned)(c - 'A');

	if(d < 6)
	{
		return (int)(d - 10);
	}

	return -1;
}

uintmax_t strntoumax(const char* nptr, char** endptr, int base, size_t n)
{
	const unsigned char* p = (const unsigned char*)nptr;
	const unsigned char* end = p + n;
	int neg = 0;
	uintmax_t v = 0;
	int d = 0;

	while(p < end && isspace(*p))
	{
		p++;
	}

	if(p < end)
	{
		char c = p[0];

		if(c == '-' || c == '+')
		{
			neg = (c == '-');
			p++;
		}
	}

	if(base == 0)
	{
		if(p + 2 < end && p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
		{
			p += 2;
			base = 16;
		}
		else if(p + 1 < end && p[0] == '0')
		{
			p += 1;
			base = 8;
		}
		else
		{
			base = 10;
		}
	}
	else if(base == 16)
	{
		if(p + 2 < end && p[0] == '0' && (p[1] == 'x' || p[1] == 'X'))
		{
			p += 2;
		}
	}

	while(p < end && (d = strntoumax_digitval(*p)) >= 0 && d < base)
	{
		v = v * base + d;
		p += 1;
	}

	if(endptr != 0)
	{
		*endptr = (char*)p;
	}

	return neg ? -v : v;
}

intmax_t strntoimax(const char* nptr, char** endptr, int base, size_t n)
{
	return (intmax_t)strntoumax(nptr, endptr, base, n);
}