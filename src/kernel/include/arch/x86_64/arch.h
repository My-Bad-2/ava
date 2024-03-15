#ifndef KERNEL_INCLUDE_ARCH_X86_64_ARCH_H
#define KERNEL_INCLUDE_ARCH_X86_64_ARCH_H

#include <stdint.h>
#include <sys/features.h>

__BEGIN_DECLS

void arch_init(void);

void arch_halt(void);
void arch_disable_interrupts(void);
void arch_enable_interrupts(void);

uint8_t inp(uint16_t port);
uint32_t inpd(uint16_t port);
uint16_t inpw(uint16_t port);

void outp(uint16_t port, uint8_t value);
void outpw(uint16_t port, uint16_t value);
void outpd(uint16_t port, uint32_t value);

__END_DECLS

#endif // KERNEL_INCLUDE_ARCH_X86_64_ARCH_H