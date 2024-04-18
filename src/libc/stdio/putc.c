#include <stdio.h>

int fputc(int ch, FILE* fp) {
	size_t write_pos = fp->position++;

	if (write_pos >= fp->max_chars) {
		return -EOF;
	}

	if (fp->write != NULL) {
		fp->write(ch, fp->extra_arg);
	} else {
		fp->buffer[write_pos] = ch;
	}

	return ch;
}

int putc(int ch, FILE* fp) {
	return fputc(ch, fp);
}

int putchar(int ch) {
	return fputc(ch, stdout);
}