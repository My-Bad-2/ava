#include <stdio.h>
#include <string.h>

/// \note The terminating null character from str is not written.
int fputs(const char* restrict str, FILE* fp) {
	const size_t length = strlen(str);

	for (size_t i = 0; i < length; ++i) {
		int ret = fputc(str[i], fp);

		if (ret != str[i]) {
			return ret;
		}
	}

	return length;
}

int puts(const char* restrict str) {
	int ret = fputs(str, stdout);
	fputc('\n', stdout);

	return ret;
}
