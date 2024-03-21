#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_H
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_H

#include <sys/features.h>
#include <stdint.h>

#define MAX_IDT_ENTRIES 256

#define IDT_TRAP 0xEF
#define IDT_USER 0x60
#define IDT_GATE 0x8E

__BEGIN_DECLS

typedef struct {
    uint16_t offset0_15;
    uint16_t selector;
    uint8_t ist_index;
    uint8_t attributes;
    uint16_t offset16_31;
    uint32_t offset32_63;
    uint32_t reserved;
} __PACKED idt_entry_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __PACKED idt_descriptor_t;

typedef struct {
    idt_entry_t entries[MAX_IDT_ENTRIES];
} __PACKED idt_t;

void idt_init(void);
void idt_update(void* descriptor);

__END_DECLS

#endif // KERNEL_INCLUDE_ARCH_X86_64_CPU_IDT_H