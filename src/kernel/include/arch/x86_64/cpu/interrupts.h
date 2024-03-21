#ifndef KERNEL_INCLUDE_ARCH_X86_64_CPU_INTERRUPTS_H
#define KERNEL_INCLUDE_ARCH_X86_64_CPU_INTERRUPTS_H

#include <stdint.h>
#include <sys/features.h>

__BEGIN_DECLS

typedef struct
{
	uint64_t rdi, rsi, rbp, rbx, rdx, rcx, rax;
	uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
	uint64_t vector;
	uint64_t err_code;
	uint64_t ip, cs, flags;
	uint64_t user_sp, user_ss;
} __PACKED interrupt_frame_t;

typedef struct stack_frame
{
	struct stack_frame* rbp;
	uint64_t rip;
} stack_frame_t;

void dump_backtrace(uint64_t rbp);
void dump_interrupt_frame(interrupt_frame_t* frame);

__END_DECLS

#endif // KERNEL_INCLUDE_ARCH_X86_64_CPU_INTERRUPTS_H