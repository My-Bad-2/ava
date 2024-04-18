#include <arch.hpp>
#include <libc/glue.hpp>
#include <limine.h>
#include <stdio.h>

extern "C" void kmain() {
	glue::libc::setup_io_streams();
	arch::init();

	printf("Hello World!\n");

	for (;;) {
		arch::pause();
	}
}