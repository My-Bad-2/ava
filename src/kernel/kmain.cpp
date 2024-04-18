#include <arch.hpp>
#include <limine.h>

extern "C" void kmain() {
	arch::init();

	for (;;) {
		arch::pause();
	}
}