#include <string.h>

char* strrchr(const char* str, int ch) {
	const char* found = NULL;
	const char* p = NULL;

	ch = (unsigned char)ch;

	if (ch == '\0') {
		return strchr(str, '\0');
	}

	while ((p = strchr(str, ch)) != NULL) {
		found = p;
		str = p + 1;
	}

	return (char*)found;
}