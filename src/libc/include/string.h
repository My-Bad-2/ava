/// \file string.h
/// \author My-Bad-2
/// \brief String manipulation functions
/// \version 0.0.1
/// \date 2024-04-16
///
/// \copyright MIT - Copyright (c) 2024

#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/// \brief Compares the first count bytes of the objects pointed to by \p lhs and \p rhs.
/// The comparison is done lexicographically.
///
/// \param lhs, rhs pointers to the objects to compare
/// \param count number of bytes to examine.
/// \return Negative value if \p lhs appears before \p rhs in lexicographical order.
/// \return Zero if \p lhs and \p rhs compare equal, or if count is zero.
/// \return Positive value if \p lhs appears after \p rhs in lexicographical order.
int memcmp(const void* lhs, const void* rhs, size_t count);

/// \brief Copies the value \p c into each of the first count characters
/// of the object pointed to by \p dest.
///
/// \param dest pointer to the object to fill
/// \param c fill byte
/// \param count number of bytes to fill
void* memset(void* dest, int c, size_t count);

/// \brief Copies \p count characters from the object pointed to by \p src to the object
/// pointed to by \p dest.
///
/// \param dest pointer to the object to copy to
/// \param src pointer to the object to copy from
/// \param count number of bytes to copy
/// \return A copy of \p dest
void* memcpy(void* restrict dest, const void* restrict src, size_t count);

/// \brief Copies \p count characters from the object pointed to by \p src to the object
/// pointed to by \p dest. The objects may overlap: copying takes place as if the characters
/// were copied to a temporary character array and then the characters were copied from
/// the array to \p dest.
///
/// \param dest pointer to the object to copy to
/// \param src pointer to the object to copy from
/// \param count number of bytes to copy
/// \return A copy of \p dest
void* memmove(void* dest, const void* src, size_t count);

/// \brief Returns the length of the given null-terminated byte string, that is, the number
/// of characters in a character array whose first element is pointed to by str up to and
/// not including the first null character.
///
/// \param str pointer to the null-terminated byte string to be examined
/// \return The length of the null-terminated byte string \p str.
size_t strlen(const char* str);

/// \brief Returns the length of the given null-terminated byte string, that is, the number
/// of characters in a character array whose first element is pointed to by str up to and
/// not including the first null character, upto at most \p count characters.
///
/// \param str pointer to the null-terminated byte string to be examined
/// \param count maximum number of characters to count
/// \return The length of the null-terminated byte string \p str.
size_t strnlen(const char* str, size_t count);

/// \brief Copies the null-terminated byte string pointed to by \p src, including the null
/// terminator, to the character array whose first element is pointed to by \p dest.
///
/// \param dest pointer to the character array to write to
/// \param src pointer to the null-terminated byte string to copy from
/// \return Returns a copy of \p dest
char* strcpy(char* restrict dest, const char* restrict src);

/// \brief Copies at most \p count characters of the character array pointed to by \p src to
/// character array pointed to by \p dest.
///
/// \param dest pointer to the character array to copy to
/// \param src pointer to the null-terminated byte string to copy from
/// \param count maximum number of characters to copy
/// \return Returns a copy of \p dest
char* strncpy(char* restrict dest, const char* restrict src, size_t count);

/// \brief Compares two null-terminated byte strings lexicographically.
///
/// \param lhs, rhs pointers to the null-terminated byte strings to compare.
/// \return Negative value if \p lhs appears before \p rhs in lexicographical order.
/// \return Zero if \p lhs and \p rhs compare equal.
/// \return Positive value if \p lhs appears after \p rhs in lexicographical order.
int strcmp(const char* lhs, const char* rhs);

/// \brief Compares at most \p count characters of two possibly null-terminated arrays.
/// The comparison is done lexicographically. Characters following the null character
/// are not compared.
///
/// \param lhs, rhs pointers to the null-terminated byte strings to compare.
/// \param count maximum number of characters to compare
/// \return Negative value if \p lhs appears before \p rhs in lexicographical order.
/// \return Zero if \p lhs and \p rhs compare equal, or if count is zero.
/// \return Positive value if \p lhs appears after \p rhs in lexicographical order.
int strncmp(const char* lhs, const char* rhs, size_t count);

/// \brief Appends a copy of the null-terminated byte string pointed to by \p src to the end
/// of the null-terminated byte string pointed to by \p dest. The character \p src[0] replaces the
/// null terminator at the end of \p dest. The resulting byte string is null-terminated.
///
/// \param dest pointer to the null-terminated byte string to append to
/// \param src pointer to the null-terminated byte string to copy from
/// \return Returns a copy of \p dest
char* strcat(char* restrict dst, const char* restrict src);

/// \brief Appends at most \p count characters from the character array pointed to by \p src,
/// stopping if the null character is found, to the end of the null-terminated byte string
/// pointed to by \p dest. The character \p src[0] replaces the null terminator at the end
/// of \p dest. The terminating null character is always appended in the end.
///
/// \param dest pointer to the null-terminated byte string to append to
/// \param src pointer to the null-terminated byte string to copy from
/// \param count maximum number of characters to copy
/// \return Returns a copy of dest
char* strncat(char* restrict dst, const char* restrict src, size_t count);

#ifdef __cplusplus
}
#endif
#endif	// _STRING_H
