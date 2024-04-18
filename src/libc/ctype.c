#include <ctype.h>

int isalnum(int c) {
	return isalpha(c) || isdigit(c);
}

int isalpha(int c) {
	return isupper(c) || islower(c);
}

int isascii(int c) {
	return c >= 0 && c <= 127;
}

int isblank(int c) {
	return c == ' ' || c == '\t';
}

int iscntrl(int c) {
	return (c >= 0 && c <= 31) || c == 127;
}

int isdigit(int c) {
	return c >= '0' && c <= '9';
}

int isgraph(int c) {
	return c > ' ' && c <= '~';
}

int islower(int c) {
	return c >= 'a' && c <= 'z';
}

int isprint(int c) {
	return c >= ' ' && c <= '~';
}

int isspace(int c) {
	return c == ' ' || (c >= '\t' && c <= '\r');
}

int isupper(int c) {
	return c >= 'A' && c <= 'Z';
}

int isxdigit(int c) {
	return isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

/// The toascii function converts the character \p c to its corresponding ASCII character code
/// by performing a bitwise AND operation with 0x7F (0111 1111 in binary), ensuring that only
/// the least significant 7 bits of the input integer are preserved.
///
/// \note If the input integer value is outside the range of ASCII characters (0 to 127),
///       the resulting ASCII character code may not represent a valid printable character.
///       Use caution when using this function with values outside the ASCII range.
int toascii(int c) {
	return c & 0x7F;
}

int tolower(int c) {
	return isupper(c) ? c + ('a' - 'A') : c;
}

int toupper(int c) {
	return islower(c) ? c - ('a' - 'A') : c;
}
