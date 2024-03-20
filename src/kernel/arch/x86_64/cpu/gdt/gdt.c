#include <log.h>
#include <cpu/gdt.h>

static gdt_t gdt = {};

static gdt_tss_t tss = {
	0, {}, 0, {}, 0, 0, 0, 0,
};

static gdt_descriptor_t gdt_descriptor = {
	sizeof(gdt_t) - 1,
	(uint64_t)&gdt,
};

void gdt_entry(gdt_entry_t* entry, uint32_t base, uint32_t limit, uint8_t granularity,
			   uint8_t flags)
{
	entry->limit0_15 = (uint16_t)(limit & 0xFFFF);
	entry->base0_15 = (uint16_t)(base & 0xFFFF);
	entry->base16_23 = (uint8_t)((base >> 16) & 0xFF);
	entry->flags = flags;
	entry->limit16_19 = (limit >> 16) & 0x0F;
	entry->granularity = granularity;
	entry->base24_31 = (uint8_t)((base >> 24) & 0xFF);
}

void gdt_tss_entry(gdt_tss_entry_t* entry, uintptr_t tss_addr)
{
	entry->len = sizeof(gdt_tss_t);
	entry->base0_15 = tss_addr & 0xFFFF;
	entry->base16_23 = (tss_addr >> 16) & 0xFF;
	entry->flags1 = 0b10001001;
	entry->flags2 = 0;
	entry->base_high24_31 = (tss_addr >> 24) & 0xFF;
	entry->base_upper32_64 = tss_addr >> 32;
	entry->reserved = 0;
}

void gdt_entry_null(gdt_entry_t* entry)
{
	return gdt_entry(entry, 0, 0, 0, 0);
}

void gdt_init(void)
{
	gdt_entry_null(&gdt.entries[GDT_NULL]);
	gdt_entry(&gdt.entries[GDT_KERNEL_CODE], 0, 0xFFFFFFFF, 0b10, 0x9A);
	gdt_entry(&gdt.entries[GDT_KERNEL_DATA], 0, 0xFFFFFFFF, 0, 0x92);
	gdt_entry(&gdt.entries[GDT_USER_DATA], 0, 0xFFFFFFFF, 0, 0xF2);
	gdt_entry(&gdt.entries[GDT_USER_CODE], 0, 0xFFFFFFFF, 0b10, 0xFA);

	gdt_tss_entry(&gdt.tss, (uintptr_t)&tss);

	gdt_update(&gdt_descriptor);
	tss_update();

	LOG_INFO("Initialized Global Descriptor Table!");
}

void gdt_load_tss(tss_t* tss)
{
	gdt_tss_entry(&gdt.tss, (uintptr_t)tss);
	tss_update();
}