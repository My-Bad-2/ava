#include <limine.h>
#include <arch.h>
#include <dev/streams.h>
#include <log.h>

void kmain(void)
{
	dev_setup_streams();
	log_set_stream(stderr);
	arch_init();

	LOG_INFO("Hello, %s!", "Ava");

	while(1)
	{
		arch_halt();
	}
}