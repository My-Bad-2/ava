/// \file stdio.h
/// \author My-Bad-2
/// \brief Standard input and output
/// \version 0.1
/// \date 2024-04-18
/// 
/// \copyright MIT - Copyright (c) 2024

#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUFSIZE (1024)
#define EOF (-1)

/// \typedef FILE
///
/// \brief Each FILE object denotes a C stream.
typedef struct __file {
	char* buffer;
	size_t position;
	size_t max_chars;

	void* extra_arg;
	void (*write)(int c, void* extra_arg);
} FILE;

extern FILE __streams[];

#define stdin (&__streams[0])
#define stdout (&__streams[1])
#define stderr (&__streams[2])

/// \brief Writes a character \p ch to the given output stream \p fp.
///
/// \param ch character to be written
/// \param fp output stream
/// \return On success, returns the written character.
/// \return On failure, returns EOF.
int fputc(int ch, FILE* fp);

/// \brief Writes every character from the null-terminated string \p str to the output
/// stream, as if by repeatedly executing \ref fputc.
///
/// \param str null-terminated string to be written
/// \param fp output stream
/// \return On success, returns a non-negative value.
/// \return On failure, returns EOF.
int fputs(const char* restrict str, FILE* fp);

/// \brief Writes a character \p ch to the given output stream \p fp.
///
/// \param ch character to be written
/// \param fp output stream
/// \return On success, returns the written character.
/// \return On failure, returns EOF.
int putc(int ch, FILE* fp);

/// \brief Writes a character \p ch to stdout.
///
/// \param ch character to be written
/// \return On success, returns the written character.
/// \return On failure, returns EOF.
int putchar(int ch);

/// \brief Writes every character from the null-terminated string \p str and
/// one additional newline character '\\n' to the output stream stdout, as if
/// by repeatedly executing fputc.
///
/// \param str character string to be written
/// \return On success, returns a non-negative value.
/// \return On failure, returns EOF.
int puts(const char* restrict str);

/// \brief Loads the data from the given locations, converts them to character
/// string equivalents and writes the results to the output stream.
///
/// \param fp output file stream to write to
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param ... arguments specifying data to print.
/// \return Number of characters transmitted to the output stream.
int fprintf(FILE* fp, const char* format, ...) __PRINTFLIKE(2, 3);

/// \brief Loads the data from the locations, defined by \p args, converts them
/// to character string equivalents and writes the results to a file stream.
///
/// \param fp output file stream to write to
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param args variable argument list containing the data to print
/// \return Number of characters transmitted to the output stream.
int vfprintf(FILE* fp, const char* format, va_list args) __PRINTFLIKE(2, 0);

/// \brief Loads the data from the given locations, converts them to character
/// string equivalents and writes the results to stdout.
///
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param ... arguments specifying data to print.
/// \return Number of characters transmitted.
int printf(const char* format, ...) __PRINTFLIKE(1, 2);

/// \brief Loads the data from the locations, defined by \p args, converts them
/// to character string equivalents and writes the results to stdout.
///
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param args variable argument list containing the data to print
/// \return Number of characters transmitted.
int vprintf(const char* format, va_list args) __PRINTFLIKE(1, 0);

/// \brief Loads the data from the given locations, converts them to character
/// string equivalents and writes the results to a character string \p buffer.
///
/// \param buffer pointer to a character string to write to
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param ... arguments specifying data to write
/// \return Number of characters written to \p buffer.
int sprintf(char* buffer, const char* format, ...) __PRINTFLIKE(2, 3);

/// \brief Loads the data from the locations, defined by \p args, converts them
/// to character string equivalents and writes the results to a character string \p buffer.
///
/// \param buffer pointer to a character string to write to
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param args variable argument list containing the data to write
/// \return Number of characters written to \p buffer.
int vsprintf(char* buffer, const char* format, va_list args) __PRINTFLIKE(2, 0);

/// \brief Loads the data from the given locations, converts them to character
/// string equivalents and writes the results to Writes the results to a character
/// string \p buffer. At most \p n - 1 characters are written. The resulting
/// string will be terminated with a null character, unless \p n is zero.
///
/// \param buffer pointer to a character string to write to
/// \param n up to n - 1 characters may be written, plus the null terminator
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param ... arguments specifying data to write
/// \return Number of characters which would have been written to \p buffer if \p n was ignored.
int snprintf(char* buffer, size_t n, const char* format, ...)
	__PRINTFLIKE(3, 4);

/// \brief Loads the data from the locations, defined by \p args, converts them
/// to character string equivalents and writes the results to a character string
/// \p buffer. At most \p n - 1 characters are written. The resulting string will
/// be terminated with a null character, unless \p n is zero.
///
/// \param buffer pointer to a character string to write to
/// \param n up to n - 1 characters may be written, plus the null terminator
/// \param format pointer to a null-terminated byte string specifying how to interpret the data
/// \param args variable argument list containing the data to write
/// \return Number of characters which would have been written to \p buffer if \p n was ignored.
int vsnprintf(char* buffer, size_t n, const char* format, va_list args)
	__PRINTFLIKE(3, 0);

#ifdef __cplusplus
}
#endif

#endif	// _STDIO_H