#include <cpu/interrupts.hpp>
#include <log.hpp>

namespace arch::cpu {
namespace {
const char* exception_messages[32] = {
	"Division By Zero",
	"Debug",
	"Non-Maskable Interrupt",
	"Breakpoint",
	"Detected Overflow",
	"Out Of Bounds",
	"Invalid Opcode",
	"No Co-processor",
	"Double Fault",
	"Co-processor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Co-processor Fault",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Control Protection Exception",
	"Reserved",
	"Hypervisor Injection Exception",
	"VMM Communication Exception",
	"Security Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
};

static void dump_interrupt_frame(interrupt_frame_t* frame) {
	printf(" CS: %#08lx RIP: %#08lx EFL: %#08lx\n", frame->cs, frame->ip,
		   frame->flags);

	printf(" RAX: %#08lx RBX: %#08lx RCX: %#08lx RDX: %#08lx\n", frame->rax,
		   frame->rbx, frame->rcx, frame->rdx);

	printf(" RSI: %#08lx RDI: %#08lx RBP: %#08lx RSP: %#08lx\n", frame->rsi,
		   frame->rdi, frame->rbp, frame->user_sp);

	printf("  R8: %#08lx  R9: %#08lx R10: %#08lx R11: %#08lx\n", frame->r8,
		   frame->r9, frame->r10, frame->r11);

	printf(" R12: %#08lx R13: %#08lx R14: %#08lx R15: %#08lx\n", frame->r12,
		   frame->r13, frame->r14, frame->r15);

	printf(" ERRC: %#08lx\n", frame->err_code);
}

static void error_handler(interrupt_frame_t* frame) {
    LOG_ERROR("Exception(%s) occurred", exception_messages[frame->vector]);

    dump_interrupt_frame(frame);

    LOG_CRITICAL("Halting System!");
}
}  // namespace

extern "C" void interrupt_handler(interrupt_frame_t* frame) {
    if(frame->vector < 0x20) {
        error_handler(frame);
    }

    LOG_CRITICAL("Interrupt %lu occurred!", frame->vector);
}
}  // namespace arch::cpu