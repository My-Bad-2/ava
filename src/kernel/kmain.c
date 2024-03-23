#include <memory/phys.h>
#include <kernel.h>
#include <arch.h>
#include <dev/streams.h>
#include <log.h>

__SECTION(".limine_requests")
volatile struct limine_memmap_request memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0,
	.response = NULL,
};

__SECTION(".limine_requests")
volatile struct limine_hhdm_request hhdm_request = {
	.id = LIMINE_HHDM_REQUEST,
	.revision = 0,
	.response = NULL,
};

uintptr_t get_hhdm_offset()
{
	return hhdm_request.response->offset;
}

void kmain(void)
{
	dev_setup_streams();
	log_set_stream(stderr);
	arch_init();
	pmm_init();

	LOG_INFO("Hello from %s v%s!", PROJECT_NAME, PROJECT_VERSION);

	while(1)
	{
		arch_halt();
	}
}