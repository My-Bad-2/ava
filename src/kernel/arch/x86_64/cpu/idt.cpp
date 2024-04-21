#include <cpu/gdt.hpp>
#include <cpu/idt.hpp>

extern "C" uintptr_t __interrupt_vector[arch::cpu::max_idt_entries];

namespace arch::cpu {
namespace {
idt_t idt_table = {};
}

void idt_descriptor_t::flush() {
	asm volatile("lidt %0" ::"memory"(*this));
}

void idt_t::fill(uintptr_t* vectors, uint16_t selector) {
	for (size_t i = 0; i < entries.max_size(); ++i) {
		entries[i] = {vectors[i], 0, IDT_GATE, selector};
	}
}

void init_idt() {
	idt_table.fill(__interrupt_vector, KERNEL_CODE_SELECTOR);

	idt_descriptor_t descriptor = {
		sizeof(idt_t) - 1,
		reinterpret_cast<uint64_t>(&idt_table),
	};

	descriptor.flush();
}
}  // namespace arch::cpu