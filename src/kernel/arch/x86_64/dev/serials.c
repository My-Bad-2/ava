#include <dev/serials.h>
#include <arch.h>

#include <stdbool.h>
#include <stddef.h>

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

void serials_write_register(uint16_t port, uint16_t reg, uint8_t val)
{
	outp(port + reg, val);
}

uint8_t serials_read_register(uint16_t port, uint16_t reg)
{
	return inp(port + reg);
}

void serials_init(uint16_t port)
{
	// Disable all interrupts
	serials_write_register(port, SERIALS_INTERRUPT_IDENTIFACTOR, 0x00);

	// Enable DLAB to set the baud rate divisor
	serials_write_register(port, SERIALS_LINE_CONTROL, SERIALS_LINE_DLAB_STATUS);

	// Set divisor to 3 (lo byte) and 0 (hi byte)
	serials_write_register(port, SERIALS_BAUD_RATE_LOW, 3);
	serials_write_register(port, SERIALS_BAUD_RATE_HIGH, 0x00);

	// Configure for 8 bits, no parity, one stop bit
	serials_write_register(port, SERIALS_LINE_CONTROL, SERIALS_LINE_DS_8);

	// Enable FIFO, clear them with 14-byte threshold
	serials_write_register(port, SERIALS_FIFO_CONTROLLER,
						   SERIALS_ENABLE_FIFO | SERIALS_FIFO_CLEAR_RECEIVE |
							   SERIALS_FIFO_CLEAR_TRANSMIT | SERIALS_FIFO_TRIGGER_LEVEL4);

	// Enable IRQs, set RTS/DSR
	serials_write_register(port, SERIALS_MODEM_CONTROL,
						   SERIALS_MODEM_RTS | SERIALS_MODEM_DTR | SERIALS_MODEM_OUT2);

	// Set in loopback mode, test the serial chip
	serials_write_register(port, SERIALS_MODEM_CONTROL,
						   SERIALS_MODEM_LOOPBACK | SERIALS_MODEM_RTS | SERIALS_MODEM_DTR |
							   SERIALS_MODEM_OUT2);

	// Test the serial chip by sending byte 0xAE
	serials_write_register(port, SERIALS_DATA, 0xAE);

	// Check if it returns the same byte
	if(serials_read_register(port, SERIALS_DATA) != 0xAE)
	{
		return;
	}

	// If the serial chip test is successful, set it in normal operation mode
	// (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
	serials_write_register(port, SERIALS_MODEM_CONTROL,
						   SERIALS_MODEM_RTS | SERIALS_MODEM_DTR | SERIALS_MODEM_OUT1 |
							   SERIALS_MODEM_OUT2);
}

void serials_putc(uint16_t port, uint8_t ch)
{
	// Wait until the Transmitter buffer empty bit in the Line status register is set
	while(!(serials_read_register(port, SERIALS_LINE_STATUS) & SERIALS_LINE_TRANSMITTER_BUF_EMPTY))
	{
		asm volatile("pause");
	}

	// Write the character `ch` to data register
	serials_write_register(port, SERIALS_DATA, ch);
}

uint8_t serials_getc(uint16_t port)
{
	// Wait until the Data Ready bit in the Line status register is set
	while(!(serials_read_register(port, SERIALS_LINE_STATUS) & SERIALS_LINE_DATA_READY))
	{
		asm volatile("pause");
	}

	// Return the 8-bit character read from the data register
	return serials_read_register(port, SERIALS_DATA);
}

void serials_write_str(uint16_t port, const char* str)
{
	// Iterate through each character and transmit it using `serials_putc`.
	for(size_t i = 0; str[i] != '\0'; i++)
	{
		serials_putc(port, str[i]);
	}
}

#undef SERIALS_DATA
#undef SERIALS_INTERRUPT
#undef SERIALS_INTERRUPT_IDENTIFACTOR
#undef SERIALS_LINE_CONTROL
#undef SERIALS_MODEM_CONTROL
#undef SERIALS_LINE_STATUS
#undef SERIALS_MODEM_STATUS
#undef SERIALS_SCRATCH

#undef SERIALS_BAUD_RATE_LOW
#undef SERIALS_BAUD_RATE_HIGH
#undef SERIALS_FIFO_CONTROLLER

#undef SERIALS_LINE_DS_5
#undef SERIALS_LINE_DS_6
#undef SERIALS_LINE_DS_7
#undef SERIALS_LINE_DS_8
#undef SERIALS_LINE_DLAB_STATUS

#undef SERIALS_MODEM_DTR
#undef SERIALS_MODEM_RTS
#undef SERIALS_MODEM_OUT1
#undef SERIALS_MODEM_OUT2
#undef SERIALS_MODEM_LOOPBACK

#undef SERIALS_INTERRUPT_WHEN_DATA_AVAILABLE
#undef SERIALS_INTERRUPT_WHEN_TRANSMITTER_EMPTY
#undef SERIALS_INTERRUPT_WHEN_BREAK_EMPTY
#undef SERIALS_INTERRUPT_WHEN_STATUS_UPDATE

#undef SERIALS_LINE_DATA_READY
#undef SERIALS_LINE_OVERRUN_ERROR
#undef SERIALS_LINE_PARITY_ERROR
#undef SERIALS_LINE_FRAMING_ERROR
#undef SERIALS_LINE_BREAK_INDICATOR
#undef SERIALS_LINE_TRANSMITTER_BUF_EMPTY
#undef SERIALS_LINE_TRANSMITTER_EMPTY
#undef SERIALS_LINE_IMPENDING_ERROR

#undef SERIALS_ENABLE_FIFO
#undef SERIALS_FIFO_CLEAR_RECEIVE
#undef SERIALS_FIFO_CLEAR_TRANSMIT
#undef SERIALS_FIFO_ENABLE_64_BYTE
#undef SERIALS_FIFO_TRIGGER_LEVEL1
#undef SERIALS_FIFO_TRIGGER_LEVEL2
#undef SERIALS_FIFO_TRIGGER_LEVEL3
#undef SERIALS_FIFO_TRIGGER_LEVEL4