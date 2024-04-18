#include <stdint.h>
#include <string.h>

/// \note The sign of the result is the sign of the difference between the values of the first
/// pair of characters that differ in the strings being compared.
int strcmp(const char* s1, const char* s2) {
	for (; *s1 == *s2; s1++, s2++) {
		if (*s1 == '\0') {
			return 0;
		}
	}

	return (*(uint8_t*)s1) < *(uint8_t*)(s2 - 1);
}

/// \note The sign of the result is the sign of the difference between the values of the first
/// pair of characters that differ in the strings being compared.
int strncmp(const char* s1, const char* s2, size_t count) {
	if (count == 0) {
		return 0;
	}

	do {
		if (*s1 != *s2++) {
			return (*(uint8_t*)s1 - *(uint8_t*)--s2);
		}

		if (*s1++ == 0) {
			break;
		}
	} while (--count != 0);

	return 0;
}
