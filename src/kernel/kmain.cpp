#include <arch.hpp>
#include <kernel.hpp>
#include <log.hpp>

#include <glue/cxxabi.h>
#include <glue/glue.hpp>

#include <memory/memory.hpp>

__SECTION(".limine_requests")
volatile LIMINE_BASE_REVISION(1);

__SECTION(".limine_requests")
volatile limine_hhdm_request hhdm_request = {
	.id = LIMINE_HHDM_REQUEST,
	.revision = 0,
	.response = nullptr,
};

__SECTION(".limine_requests")
volatile limine_memmap_request memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0,
	.response = nullptr,
};

extern "C" void kmain() {
	cxxabi::init();
	glue::setup_io_streams();

	arch::early_init();
	memory::init();
	arch::init();

	LOG_INFO("Hello World!");

	while (true) {
		arch::pause();
	}
}