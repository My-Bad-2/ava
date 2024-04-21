#include <arch.hpp>
#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>
#include <dev/serials.hpp>

/// This inline assembly function reads a byte from the specified I/O port using the `INB` (Input Byte)
/// assembly instruction. The result is stored in the provided variable.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
uint8_t inp(uint16_t port) {
	uint8_t ret = 0;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

/// This inline assembly function reads a word (16 bits) from the specified I/O port using the `INW`
/// (Input Word) assembly instruction. The result is stored in the provided variable.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
uint16_t inpw(uint16_t port) {
	uint16_t ret = 0;
	asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

/// This inline assembly function reads a double word (32 bits) from the specified I/O port using the `INL`
/// (Input Long) assembly instruction. The result is stored in the provided variable.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
uint32_t inpd(uint16_t port) {
	uint32_t ret = 0;
	asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

/// This inline assembly function writes a byte to the specified I/O port using the `OUTB` (Output Byte)
/// assembly instruction.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
void outp(uint16_t port, uint8_t value) {
	asm volatile("outb %1, %0" ::"Nd"(port), "a"(value));
}

/// This inline assembly function writes a word (16 bits) to the specified I/O port using the `OUTW` (Output Word)
/// assembly instruction.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
void outpw(uint16_t port, uint16_t value) {
	asm volatile("outw %1, %0" ::"Nd"(port), "a"(value));
}

/// This inline assembly function writes a double word (32 bits) to the specified I/O port using the `OUTL` (Output Long)
/// assembly instruction.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
void outpd(uint16_t port, uint32_t value) {
	asm volatile("outl %1, %0" ::"Nd"(port), "a"(value));
}

namespace arch {
namespace {
constinit dev::serials serial_device = {};
}

/// This inline assembly function executes the `HLT` (Halt) assembly instruction, which puts the processor
/// into a halt state, causing it to cease executing instructions until an interrupt or external event occurs.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
void halt() {
	asm volatile("hlt");
}

/// This inline assembly function executes the `STI` (Set Interrupt Enable) assembly instruction,
/// which enables interrupts. Enabling interrupts allows the processor to respond to external
/// hardware and software-generated interrupt requests.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
void enable_interrupts() {
	asm volatile("sti");
}

/// This inline assembly function executes the `CLI` (Clear Interrupt Enable) assembly instruction,
/// which disables interrupts. Disabling interrupts prevents the processor from responding to
/// external hardware and software-generated interrupt requests.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
void disable_interrupts() {
	asm volatile("cli");
}

/// This inline assembly function executes the `PAUSE` instruction, which is a hint to the processor
/// that the current execution is a busy-wait loop. It can improve the performance of busy-wait loops
/// by providing a hint to the processor to reduce power consumption.
///
/// \note This function is marked as volatile to indicate to the compiler that the assembly instruction
/// has side effects and should not be optimized out.
void pause() {
	asm volatile("pause");
}

void init() {
	disable_interrupts();

	// Initialize the serial device, return if the serial chip is faulty.
	serial_device.set_port(SERIAL_COM_PORT_1);

	if (!serial_device.init()) {
		return;
	}

	cpu::init_gdt();
	cpu::init_idt();

	enable_interrupts();
}

void write(const char* str) {
	serial_device.write(str);
}

void write(int ch) {
	serial_device.putc(ch);
}
}  // namespace arch