#include <stdio.h>
#include <string.h>

int fputs(const char* restrict s, FILE* fp)
{
	const size_t len = strlen(s);

	for(size_t i = 0; i < len; i++)
	{
		int ret = fputc(s[i], fp);

		if(ret != 1)
		{
			return ret;
		}
	}

	return 1;
}

int puts(const char* restrict s)
{
	return fputs(s, stdout);
}