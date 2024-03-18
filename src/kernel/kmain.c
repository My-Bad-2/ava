#include <limine.h>
#include <arch.h>
#include <dev/streams.h>
#include <stdio.h>

void kmain(void)
{
	dev_setup_streams();
	arch_init();

	printf("Hello, World!\n");

	while(1)
	{
		arch_halt();
	}
}