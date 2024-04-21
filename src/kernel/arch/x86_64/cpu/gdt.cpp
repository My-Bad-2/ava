#include <cpu/gdt.hpp>
#include <log.hpp>

extern "C" {
void gdt_update(arch::cpu::gdt_descriptor_t*);
void tss_update();
}

namespace arch::cpu {
namespace {
gdt_t gdt_table = {};
tss_t tss = {};
}  // namespace

void gdt_descriptor_t::flush() {
	gdt_update(this);
	tss_update();
}

void init_gdt() {
	gdt_table.null = {};
	gdt_table.kernel_code = {0, 0xFFFFFFFF, 0x2, 0x9A};
	gdt_table.kernel_data = {0, 0xFFFFFFFF, 0, 0x92};
	gdt_table.user_data = {0, 0xFFFFFFFF, 0, 0xF2};
	gdt_table.user_code = {0, 0xFFFFFFFF, 0x2, 0xFA};

	gdt_table.tss = {&tss};

	gdt_descriptor_t descriptor = {
		sizeof(gdt_t) - 1,
		reinterpret_cast<uint64_t>(&gdt_table),
	};

	descriptor.flush();

	LOG_INFO("Initialized Global Descriptor Table.");
}
}  // namespace arch::cpu