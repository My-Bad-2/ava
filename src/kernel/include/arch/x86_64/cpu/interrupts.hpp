#ifndef ARCH_CPU_INTERRUPTS_HPP
#define ARCH_CPU_INTERRUPTS_HPP

#include <stdint.h>
#include <sys/cdefs.h>

namespace arch::cpu {
struct interrupt_frame_t {
	uint64_t rdi, rsi, rbp, rbx, rdx, rcx, rax;
	uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
	uint64_t vector;
	uint64_t err_code;
	uint64_t ip, cs, flags;
	uint64_t user_sp, user_ss;
} __PACKED;


}  // namespace arch::cpu

#endif	// ARCH_CPU_INTERRUPTS_HPP