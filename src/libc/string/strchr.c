#include <stdint.h>
#include <string.h>

char* strchr(const char* str, int ch) {
	const uint8_t* ptr = NULL;
	const size_t* longword_ptr = NULL;
	size_t longword = 0;
	size_t magic_bits = 0;
	size_t charmask = 0;
	uint8_t c = (uint8_t)ch;

	for (ptr = (const uint8_t*)str; ((size_t)ptr & (sizeof(size_t) - 1)) != 0;
		 ++ptr) {
		if (*ptr == c) {
			return (void*)ptr;
		} else if (*ptr == '\0') {
			return NULL;
		}
	}

	longword_ptr = (size_t*)ptr;

	magic_bits = -1;
	magic_bits = magic_bits / 0xFF * 0xFE << 1 >> 1 | 1;

	charmask = c | (c << 8);
	charmask |= charmask << 16;

	if (sizeof(longword) > 4) {
		charmask |= (charmask << 16) << 16;
	}

	while (1) {
		longword = *longword_ptr++;

		if ((((longword + magic_bits) ^ ~longword) & ~magic_bits) != 0 ||
			((((longword ^ charmask) + magic_bits) ^ ~(longword ^ charmask)) &
			 ~magic_bits) != 0) {
			const uint8_t* cp = (const uint8_t*)(longword_ptr - 1);

			if (*cp == c) {
				return (char*)cp;
			} else if (*cp == '\0') {
				return NULL;
			}

			if (*++cp == c) {
				return (char*)cp;
			} else if (*cp == '\0') {
				return NULL;
			}

			if (*++cp == c) {
				return (char*)cp;
			} else if (*cp == '\0') {
				return NULL;
			}

			if (*++cp == c) {
				return (char*)cp;
			} else if (*cp == '\0') {
				return NULL;
			}

			if (sizeof(longword) > 4) {
				if (*++cp == c) {
					return (char*)cp;
				} else if (*cp == '\0') {
					return NULL;
				}

				if (*++cp == c) {
					return (char*)cp;
				} else if (*cp == '\0') {
					return NULL;
				}

				if (*++cp == c) {
					return (char*)cp;
				} else if (*cp == '\0') {
					return NULL;
				}

				if (*++cp == c) {
					return (char*)cp;
				} else if (*cp == '\0') {
					return NULL;
				}
			}
		}
	}

	return NULL;
}
