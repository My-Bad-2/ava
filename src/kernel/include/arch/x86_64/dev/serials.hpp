#ifndef ARCH_DEV_SERIALS_HPP
#define ARCH_DEV_SERIALS_HPP

#include <stdint.h>

#define SERIAL_COM_PORT_1 0x3F8
#define SERIAL_COM_PORT_2 0x2F8
#define SERIAL_COM_PORT_3 0x3E8
#define SERIAL_COM_PORT_4 0x2E8

namespace dev {
class serials {
    constexpr serials() = default;

    constexpr serials(uint16_t port) : port(port) {}

    void init(uint16_t port);

    void putc(uint8_t ch);
    uint8_t getc();

    void write_str(const char* str);

   private:
    void write_register(uint16_t reg, uint8_t val);
    uint8_t read_register(uint16_t reg);

    uint16_t port;
};
}  // namespace dev

#endif  // ARCH_DEV_SERIALS_HPP