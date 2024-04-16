#include <stdint.h>
#include <string.h>

/// The sign of the result is the sign of the difference between the values of the
/// first pair of bytes that differ in the objects being compared.
int memcmp(const void* lhs, const void* rhs, size_t count) {
    register const uint8_t* str1 = lhs;
    register const uint8_t* str2 = rhs;

    if (count == 0) {
        return 0;
    }

    do {
        if (*str1++ != *str2++) {
            return *--str1 - *--str2;
        }
    } while (--count != 0);

    return 0;
}
