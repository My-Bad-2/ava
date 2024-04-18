/// \file ctype.h
/// \author My-Bad-2
/// \brief Declare character classification functions
/// \version 0.0.1
/// \date 2024-04-16
///
/// \copyright MIT - Copyright (c) 2024

#ifndef _CTYPE_H
#define _CTYPE_H

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/// \brief Checks if the given character is an alphanumeric character.
///
/// \param c character to classify
/// \return Non-zero value if the character is an alphanumeric character, zero otherwise.
int isalnum(int c);

/// \brief Checks if the given character is an alphabetic character, i.e. either an uppercase letter, or a lowercase letter.
///
/// \param c character to classify
/// \return Non-zero value if the character is an alphabetic character, zero otherwise.
int isalpha(int c);

/// \brief Checks if the given character is a blank character, i.e. space (0x20), and horizontal tab (0x09).
///
/// \param c character to classify
/// \return Non-zero value if the character is a blank character, zero otherwise.
int isblank(int c);

/// \brief Checks if the given character is a control character, i.e. codes 0x00-0x1F and 0x7F.
///
/// \param c character to classify
/// \return Non-zero value if the character is a control character, zero otherwise.
int iscntrl(int c);

/// \brief Checks if the given character is a numeric character.
///
/// \param c character to classify
/// \return Non-zero value if the character is a numeric character, zero otherwise.
int isdigit(int c);

/// \brief Checks if the given character has a graphical representation, i.e. it is either
/// a number, an uppercase letter, a lowercase letter, or a punctuation character.
///
/// \param c character to classify
/// \return Non-zero value if the character has a graphical character, zero otherwise.
int isgraph(int c);

/// \brief Checks if the given character is classified as a lowercase character.
///
/// \param c character to classify
/// \return Non-zero value if the character is a lowercase letter, zero otherwise.
int islower(int c);

/// \brief Checks if the given character can be printed, i.e. it is either a number, an
/// uppercase letter, a lowercase letter, a punctuation character, or space.
///
/// \param c character to classify
/// \return Non-zero value if the character can be printed, zero otherwise.
int isprint(int c);

/// \brief Checks if the given character is a punctuation character.
///
/// \param c character to classify
/// \return Non-zero value if the character is a punctuation character, zero otherwise.
int ispunct(int c);

/// \brief Checks if the given character is either
/// - A standard white-space character:
///     - Space (0x20, ' '),
///     - Form feed (0x0c, '\\f'),
///     - Line feed (0x0a, '\\n'),
///     - Carriage return (0x0d, '\\r'),
///     - Horizontal tab (0x09, '\\t'),
///     - Vertical tab (0x0b, '\\v'),88
///
/// \param c character to classify
/// \return Non-zero value if the character is a whitespace character, zero otherwise.
int isspace(int c);

/// \brief Checks if the given character is classified as a uppercase character.
///
/// \param c character to classify
/// \return Non-zero value if the character is a uppercase letter, zero otherwise.
int isupper(int c);

/// \brief Checks if the given character is a hexadecimal numeric character.
///
/// \param c character to classify
/// \return Non-zero value if the character is a hexadecimal numeric character, zero otherwise.
int isxdigit(int c);

/// \brief Converts the given character to lowercase according to the character conversion rules.
///
/// \param c character to be converted
/// \return Lowercase version of \p c or unmodified \p c if no lowercase version.
int tolower(int c);

/// \brief Converts the given character to uppercase according to the character conversion rules.
///
/// \param c character to be converted
/// \return Lowercase version of \p c or unmodified \p c if no uppercase version.
int toupper(int c);

/// \brief Converts the given character to its corresponding ASCII character code.
///
/// \param c character to be converted
/// \return The ASCII character code corresponding to the character.
int toascii(int c);

#ifdef __cplusplus
}
#endif
#endif	// _CTYPE_H
