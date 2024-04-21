#ifndef ARCH_CPU_IDT_HPP
#define ARCH_CPU_IDT_HPP

#include <array>
#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

namespace arch::cpu {
constexpr size_t max_idt_entries = 256;

enum idt_flags : uint16_t {
	IDT_GATE = 0x8E,
	IDT_USER = 0x60,
	IDT_TRAP = 0xEF,
};

struct idt_entry_t {
	uint16_t offset0_15;
	uint16_t selector;
	uint8_t ist_index;
	uint8_t attributes;
	uint16_t offset16_31;
	uint32_t offset32_63;
	uint32_t reserved;

	constexpr idt_entry_t() = default;

	idt_entry_t(uintptr_t handler, uint8_t ist, uint8_t flags,
				uint16_t selector)
		: offset0_15(handler & 0xFFFF), selector(selector), ist_index(ist),
		  attributes(flags), offset16_31((handler >> 16) & 0xFFFF),
		  offset32_63((handler >> 32) & 0xFFFFFFFF), reserved(0) {}

	uint64_t offset() {
		return offset0_15 | (offset16_31 << 16) | (static_cast<uint64_t>(offset32_63) << 32);
	}
} __PACKED;

struct idt_descriptor_t {
	uint16_t limit;
	uint64_t base;

	constexpr idt_descriptor_t() = default;

	constexpr idt_descriptor_t(uint16_t limit, uint64_t base)
		: limit(limit), base(base) {}

	void flush();
} __PACKED;

struct idt_t {
	std::array<idt_entry_t, max_idt_entries> entries;

	constexpr idt_t() = default;

	idt_entry_t& operator[](size_t index) { return this->entries[index]; }

	constexpr size_t max_entries() { return entries.max_size(); }

	void fill(uintptr_t* vectores, uint16_t selector);
} __PACKED;

void init_idt();
}  // namespace arch::cpu

#endif	// ARCH_CPU_IDT_HPP