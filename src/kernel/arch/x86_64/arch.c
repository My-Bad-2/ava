#include <arch.hpp>

uint8_t inp(uint16_t port) {
    uint8_t ret = 0;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

uint16_t inpw(uint16_t port) {
    uint16_t ret = 0;
    asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

uint32_t inpd(uint16_t port) {
    uint32_t ret = 0;
    asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outp(uint16_t port, uint8_t value) {
    asm volatile("outb %1, %0" ::"Nd"(port), "a"(value));
}

void outpw(uint16_t port, uint16_t value) {
    asm volatile("outw %1, %0" ::"Nd"(port), "a"(value));
}

void outpd(uint16_t port, uint32_t value) {
    asm volatile("outl %1, %0" ::"Nd"(port), "a"(value));
}
