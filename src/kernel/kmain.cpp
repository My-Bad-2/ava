#include <arch.hpp>
#include <libc/glue.hpp>
#include <limine.h>
#include <log.hpp>

extern "C" void kmain() {
	glue::libc::setup_io_streams();
	arch::init();

	LOG_INFO("Hello World!");

	for (;;) {
		arch::pause();
	}
}