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

int toascii(int c) {
    return c & 0x7F;
}

int tolower(int c) {
    return isupper(c) ? c + ('a' - 'A') : c;
}

int toupper(int c) {
    return islower(c) ? c - ('a' - 'A') : c;
}
