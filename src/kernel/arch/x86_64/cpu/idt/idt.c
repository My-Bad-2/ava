#include <cpu/gdt.h>
#include <cpu/idt.h>
#include <log.h>

extern uintptr_t __interrupt_vector[256];

static idt_t idt = {};

static idt_descriptor_t idt_descriptor = {
	sizeof(idt_t) - 1,
	(uint64_t)&idt,
};

void idt_entry(idt_entry_t* entry, uintptr_t handler, uint8_t ist, uint8_t flags)
{
	entry->offset0_15 = handler & 0xFFFF;
	entry->selector = (GDT_KERNEL_CODE * 8);
	entry->ist_index = ist;
	entry->attributes = flags;
	entry->offset16_31 = (handler >> 16) & 0xFFFF;
	entry->offset32_63 = (handler >> 32) & 0xFFFFFFFF;
	entry->reserved = 0;
}

void idt_init(void)
{
	for(int i = 0; i < 256; i++)
	{
		idt_entry(&idt.entries[i], __interrupt_vector[i], 0, IDT_GATE);
	}

	idt_update(&idt_descriptor);

	LOG_INFO("Initialized Interrupt Descriptor Tables!");
}