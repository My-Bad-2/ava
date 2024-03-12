#ifndef KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H
#define KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H

#include <stdint.h>

#define SERIAL_COM_PORT_1 0x3F8
#define SERIAL_COM_PORT_2 0x2F8
#define SERIAL_COM_PORT_3 0x3E8
#define SERIAL_COM_PORT_4 0x2E8

#define SERIAL_COM_DEFAULT SERIAL_COM_PORT_1

void serials_init(uint16_t port);

void serials_putc(uint16_t port, uint8_t ch);
uint8_t serials_getc(uint16_t port);

void serials_write_str(uint16_t port, const char* str);

#endif // KERNEL_INCLUDE_ARCH_X86_64_DEV_SERIALS_H