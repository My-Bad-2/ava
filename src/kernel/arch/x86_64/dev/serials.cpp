#include "errors.h"
#include <arch.hpp>
#include <cstdint>
#include <dev/serials.hpp>

#define SERIALS_DATA 0
#define SERIALS_INTERRUPT 1
#define SERIALS_INTERRUPT_IDENTIFACTOR 2
#define SERIALS_LINE_CONTROL 3
#define SERIALS_MODEM_CONTROL 4
#define SERIALS_LINE_STATUS 5
#define SERIALS_MODEM_STATUS 6
#define SERIALS_SCRATCH 7

#define SERIALS_BAUD_RATE_LOW SERIALS_DATA
#define SERIALS_BAUD_RATE_HIGH SERIALS_INTERRUPT
#define SERIALS_FIFO_CONTROLLER SERIALS_INTERRUPT_IDENTIFACTOR

#define SERIALS_LINE_DS_5 0
#define SERIALS_LINE_DS_6 1
#define SERIALS_LINE_DS_7 2
#define SERIALS_LINE_DS_8 3
#define SERIALS_LINE_DLAB_STATUS (1 << 7)

#define SERIALS_MODEM_DTR (1 << 0)
#define SERIALS_MODEM_RTS (1 << 1)
#define SERIALS_MODEM_OUT1 (1 << 2)
#define SERIALS_MODEM_OUT2 (1 << 3)
#define SERIALS_MODEM_LOOPBACK (1 << 4)

#define SERIALS_INTERRUPT_WHEN_DATA_AVAILABLE (1 << 0)
#define SERIALS_INTERRUPT_WHEN_TRANSMITTER_EMPTY (1 << 1)
#define SERIALS_INTERRUPT_WHEN_BREAK_EMPTY (1 << 2)
#define SERIALS_INTERRUPT_WHEN_STATUS_UPDATE (1 << 3)

#define SERIALS_LINE_DATA_READY (1 << 0)
#define SERIALS_LINE_OVERRUN_ERROR (1 << 1)
#define SERIALS_LINE_PARITY_ERROR (1 << 2)
#define SERIALS_LINE_FRAMING_ERROR (1 << 3)
#define SERIALS_LINE_BREAK_INDICATOR (1 << 4)
#define SERIALS_LINE_TRANSMITTER_BUF_EMPTY (1 << 5)
#define SERIALS_LINE_TRANSMITTER_EMPTY (1 << 6)
#define SERIALS_LINE_IMPENDING_ERROR (1 << 7)

#define SERIALS_ENABLE_FIFO (1 << 0)
#define SERIALS_FIFO_CLEAR_RECEIVE (1 << 1)
#define SERIALS_FIFO_CLEAR_TRANSMIT (1 << 2)
#define SERIALS_FIFO_ENABLE_64_BYTE (1 << 5)
#define SERIALS_FIFO_TRIGGER_LEVEL1 (0 << 6)
#define SERIALS_FIFO_TRIGGER_LEVEL2 (1 << 6)
#define SERIALS_FIFO_TRIGGER_LEVEL3 (2 << 6)
#define SERIALS_FIFO_TRIGGER_LEVEL4 (3 << 6)

namespace dev {
void serials::write_register(uint16_t reg, uint8_t val) {
	outp(this->port + reg, val);
}

uint8_t serials::read_register(uint16_t reg) {
	return inp(this->port + reg);
}

std::expected<void, error_codes> serials::init() {
	// Disable all interrupts
	this->write_register(SERIALS_INTERRUPT_IDENTIFACTOR, 0x00);

	// Enable DLAB to set the baud rate divisor
	this->write_register(SERIALS_LINE_CONTROL, SERIALS_LINE_DLAB_STATUS);

	// Set divisor to 3 (lo bytes) and 0 (hi byte)
	this->write_register(SERIALS_BAUD_RATE_LOW, 3);
	this->write_register(SERIALS_BAUD_RATE_HIGH, 0);

	// Configure for 8 bits, no parity, one stop bit
	this->write_register(SERIALS_LINE_CONTROL, SERIALS_LINE_DS_8);

	// Enable FIFO, clear them with 14-byte threshold
	this->write_register(SERIALS_FIFO_CONTROLLER,
						 SERIALS_ENABLE_FIFO | SERIALS_FIFO_CLEAR_RECEIVE |
							 SERIALS_FIFO_CLEAR_TRANSMIT |
							 SERIALS_FIFO_TRIGGER_LEVEL4);

	// Enable IRQs, set RTS/DSR
	this->write_register(SERIALS_MODEM_CONTROL, SERIALS_MODEM_RTS |
													SERIALS_MODEM_DTR |
													SERIALS_MODEM_OUT2);

	// Set in loopback mode, test the serial chip
	this->write_register(SERIALS_MODEM_CONTROL,
						 SERIALS_MODEM_LOOPBACK | SERIALS_MODEM_RTS |
							 SERIALS_MODEM_DTR | SERIALS_MODEM_OUT2);

	// Test the serial chip by sending byte 0xAE
	this->write_register(SERIALS_DATA, 0xAE);

	if (this->read_register(SERIALS_DATA) != 0xAE) {
		return std::unexpected(ERROR_FAULT);
	}

	this->write_register(SERIALS_MODEM_CONTROL,
						 SERIALS_MODEM_RTS | SERIALS_MODEM_DTR |
							 SERIALS_MODEM_OUT1 | SERIALS_MODEM_OUT2);

	return {};
}

void serials::putc(uint8_t ch) {
	while (!(this->read_register(SERIALS_LINE_STATUS) &
			 SERIALS_LINE_TRANSMITTER_BUF_EMPTY)) {
		arch::pause();
	}

	this->write_register(SERIALS_DATA, ch);
}

uint8_t serials::getc() {
	while (
		!(this->read_register(SERIALS_LINE_STATUS) & SERIALS_LINE_DATA_READY)) {
		arch::pause();
	}

	return this->read_register(SERIALS_DATA);
}

void serials::set_port(uint16_t port) {
	this->port = port;
}

void serials::write(const char* str) {
	for (size_t i = 0; str[i] != '\0'; ++i) {
		this->putc(str[i]);
	}
}
}  // namespace dev