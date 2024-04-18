/// @file serials.hpp
/// @author My-Bad-2
/// @brief Serial communication device
/// @version 0.1
/// @date 2024-04-18
///
/// @copyright Copyright (c) 2024

#ifndef ARCH_DEV_SERIALS_HPP
#define ARCH_DEV_SERIALS_HPP

#include <errors.h>
#include <expected>
#include <stdint.h>

#define SERIAL_COM_PORT_1 0x3F8
#define SERIAL_COM_PORT_2 0x2F8
#define SERIAL_COM_PORT_3 0x3E8
#define SERIAL_COM_PORT_4 0x2E8

namespace dev {
/// \class serials
///
/// \brief Serial communication device.
class serials {
   public:
	constexpr serials() = default;

	constexpr serials(uint16_t port) : port(port) {}

	/// \brief Initialize the serial port device.
	///
	/// \return An error if the serial chip is faulty.
	std::expected<void, error_codes> init();

	/// \brief Transmit a single character over the serial port.
	///
	/// \param ch The character to be transmitted.
	void putc(uint8_t ch);

	/// \brief Receive a single character from the serial port.
	///
	/// \return The received 8-bit character
	uint8_t getc();

	/// \brief Write a null-terminated string to the serial port.
	///
	/// \param str Pointer to the null-terminated string
	void write(const char* str);

	/// \brief Set the serial port base address.
	///
	/// \param port Port base address
	void set_port(uint16_t port);

   private:
	/// \brief Write \p val to a specified register of the serial port.
	///
	/// \param reg The register to write to
	/// \param val The 8-bit value to be written
	void write_register(uint16_t reg, uint8_t val);

	/// \brief Read the value from a specified register of the serial port.
	///
	/// \param reg The register to read from
	/// \return The 8-bit value read from \p reg
	uint8_t read_register(uint16_t reg);

	/// Base address of the serial port.
	uint16_t port;
};
}  // namespace dev

#endif	// ARCH_DEV_SERIALS_HPP