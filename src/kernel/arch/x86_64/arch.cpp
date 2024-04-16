#include <arch.hpp>

namespace arch {
void halt() {
    asm volatile("hlt");
}

void enable_interrupts() {
    asm volatile("sti");
}

void disable_interrupts() {
    asm volatile("cli");
}

void pause() {
    asm volatile("pause");
}

void init() {}
}  // namespace arch