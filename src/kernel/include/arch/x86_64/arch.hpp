#ifndef ARCH_ARCH_HPP
#define ARCH_ARCH_HPP

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

uint8_t inp(uint16_t port);
uint32_t inpd(uint16_t port);
uint16_t inpw(uint16_t port);

void outp(uint16_t port, uint8_t value);
void outpw(uint16_t port, uint16_t value);
void outpd(uint16_t port, uint32_t value);

__END_DECLS

#ifdef __cplusplus

namespace arch {
void halt();
void pause();
void disable_interrupts();
void enable_interrupts();

void init();
}  // namespace arch

#endif  // __cplusplus
#endif  // ARCH_ARCH_HPP
