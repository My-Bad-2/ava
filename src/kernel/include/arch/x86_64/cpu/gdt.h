#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_H
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_H

#include <stdint.h>
#include <sys/features.h>
#include <threads.h>

#define GDT_ENTRY_COUNT 5

#define GDT_NULL (0)
#define GDT_KERNEL_CODE (1)
#define GDT_KERNEL_DATA (2)
#define GDT_USER_DATA (3)
#define GDT_USER_CODE (4)

__BEGIN_DECLS

typedef struct
{
	uint16_t limit0_15;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t flags;
	uint8_t limit16_19 : 4;
	uint8_t granularity : 4;
	uint8_t base24_31;
} __PACKED gdt_entry_t;

typedef struct
{
	uint16_t limit;
	uint64_t base;
} __PACKED gdt_descriptor_t;

typedef struct
{
	uint16_t len;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t flags1;
	uint8_t flags2;
	uint8_t base_high24_31;
	uint32_t base_upper32_64;
	uint32_t reserved;
} __PACKED gdt_tss_entry_t;

typedef struct
{
	uint32_t reserved;
	uint64_t rsp[3];
	uint64_t reserved0;
	uint64_t ist[7];
	uint32_t reserved1;
	uint32_t reserved2;
	uint16_t reserved3;
	uint16_t iopb_offset;
} __PACKED gdt_tss_t;

typedef struct
{
	gdt_entry_t entries[GDT_ENTRY_COUNT];
	gdt_tss_entry_t tss;
} __PACKED gdt_t;

void gdt_init(void);
void gdt_load_tss(tss_t* tss);

extern void gdt_update(void* descriptor);
extern void tss_update(void);

__END_DECLS

#endif // KERNEL_INCLUDE_ARCH_X86_64_CPU_GDT_H