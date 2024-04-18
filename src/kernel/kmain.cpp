#include <arch.hpp>
#include <limine.h>

extern "C" void kmain() {
	arch::init();
	arch::write("Hello World!\n");

	for (;;) {
		arch::pause();
	}
}