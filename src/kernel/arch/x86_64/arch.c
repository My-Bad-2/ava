#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <dev/serials.h>
#include <arch.h>

void arch_halt(void)
{
	asm volatile("hlt");
}

void arch_enable_interrupts(void)
{
	asm volatile("sti");
}

void arch_disable_interrupts(void)
{
	asm volatile("cli");
}

void arch_pause(void) {
	asm volatile("pause");
}

uint8_t inp(uint16_t port)
{
	uint8_t ret = 0;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

uint16_t inpw(uint16_t port)
{
	uint16_t ret = 0;
	asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

uint32_t inpd(uint16_t port)
{
	uint32_t ret = 0;
	asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

void outp(uint16_t port, uint8_t value)
{
	asm volatile("outb %1, %0" ::"Nd"(port), "a"(value));
}

void outpw(uint16_t port, uint16_t value)
{
	asm volatile("outw %1, %0" ::"Nd"(port), "a"(value));
}

void outpd(uint16_t port, uint32_t value)
{
	asm volatile("outl %1, %0" ::"Nd"(port), "a"(value));
}

uint64_t arch_save_flags(void)
{
	uint64_t state;

	asm volatile("pushf;"
				 "pop %0"
				 : "=rm"(state)::"memory");

	return state;
}

void arch_restore_flags(uint64_t flags)
{
	asm volatile("push %0;"
				 "popf" ::"g"(flags)
				 : "memory", "cc");
}

void arch_init(void)
{
	arch_disable_interrupts();

	serials_init(SERIAL_COM_DEFAULT);

	gdt_init();
	idt_init();

	arch_enable_interrupts();
}