#include <stdint.h>
#include <stdio.h>
#include <dev/streams.h>
#include <dev/serials.h>

FILE __streams[3] = {};

void dev_serial_putchar(int c, void* extra_arg)
{
	(void)extra_arg;
	return serials_putc(SERIAL_COM_DEFAULT, c);
}

void dev_setup_stream(FILE* fp, void (*write)(int, void*), void* extra_arg)
{
	fp->buffer = NULL;
	fp->write = write;
	fp->extra_arg = extra_arg;
	fp->max_chars = SIZE_MAX;
	fp->position = 0;
}

void dev_setup_streams(void)
{
	dev_setup_stream(stdin, dev_serial_putchar, NULL);
	dev_setup_stream(stdout, dev_serial_putchar, NULL);
	dev_setup_stream(stderr, dev_serial_putchar, NULL);
}