#include <limine.h>
#include <arch.h>

void kmain(void)
{
	arch_init();

	while(1)
	{
		arch_halt();
	}
}