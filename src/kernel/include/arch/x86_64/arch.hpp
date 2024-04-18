/// \file arch.hpp
/// \author My-Bad-2
/// \brief Architecture specific functions
/// \version 0.0.1
/// \date 2024-04-16
///
/// \copyright MIT - Copyright (c) 2024

#ifndef ARCH_ARCH_HPP
#define ARCH_ARCH_HPP

#include <stdint.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/// \brief Read a byte from the specified I/O port.
///
/// \param port The I/O port from which to read the byte.
/// \return The byte read from the specified I/O port.
uint8_t inp(uint16_t port);

/// \brief Read a word (16 bits) from the specified I/O port.
///
/// \param port The I/O port from which to read the word.
/// \return The word read from the specified I/O port.
uint16_t inpw(uint16_t port);

/// \brief Read a double word (32 bits) from the specified I/O port.
///
/// \param port The I/O port from which to read the double word.
/// \return The double word read from the specified I/O port.
uint32_t inpd(uint16_t port);

/// \brief Write a byte to the specified I/O port.
///
/// \param port The I/O port to which to write the byte.
/// \param data The byte to write to the specified I/O port.
void outp(uint16_t port, uint8_t value);

/// \brief Write a word (16 bits) to the specified I/O port.
///
/// \param port The I/O port to which to write the word.
/// \param data The word to write to the specified I/O port.
void outpw(uint16_t port, uint16_t value);

/// \brief Write a double word (32 bits) to the specified I/O port.
///
/// \param port The I/O port to which to write the double word.
/// \param data The double word to write to the specified I/O port.
void outpd(uint16_t port, uint32_t value);

#ifdef __cplusplus
}
#endif

namespace arch {
/// \brief Halt the processor.
void halt();

/// \brief Pause instruction for busy-wait loops.
void pause();

/// \brief Disable interrupts.
void disable_interrupts();

/// \brief Enable interrupts.
void enable_interrupts();

/// \brief Initialize Architecture-specific components.
void init();

/// \brief Write a string to stdout.
///
/// \param str string to write
void write(const char* str);
}  // namespace arch

#endif	// ARCH_ARCH_HPP
