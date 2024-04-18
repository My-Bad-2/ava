#include <arch.hpp>
#include <libc/glue.hpp>
#include <stdio.h>

FILE __streams[3] = {};

namespace glue::libc {
namespace {
void putchar(int ch, void*) {
	return arch::write(ch);
}

void setup_streams(FILE* fp, void (*write)(int, void*), void* extra_arg) {
	fp->buffer = NULL;
	fp->write = write;
	fp->extra_arg = extra_arg;
	fp->max_chars = SIZE_MAX;
	fp->position = 0;
}
}  // namespace

void setup_io_streams() {
	setup_streams(stdin, putchar, NULL);
	setup_streams(stdout, putchar, NULL);
	setup_streams(stderr, putchar, NULL);
}
}  // namespace glue::libc