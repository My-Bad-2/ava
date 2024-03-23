#include <log.h>
#include <cpu/interrupts.h>

static char* interrupt_exception_messages[32] = {
	"DivisionByZero",
	"Debug",
	"NonMaskableInterrupt",
	"Breakpoint",
	"DetectedOverflow",
	"OutOfBounds",
	"InvalidOpcode",
	"NoCoprocessor",
	"DoubleFault",
	"CoprocessorSegmentOverrun",
	"BadTss",
	"SegmentNotPresent",
	"StackFault",
	"GeneralProtectionFault",
	"PageFault",
	"UnknownInterrupt",
	"CoprocessorFault",
	"AlignmentCheck",
	"MachineCheck",
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

void dump_backtrace(uint64_t rbp)
{
	stack_frame_t* stackframe = (stack_frame_t*)rbp;

	while(stackframe)
	{
		printf(" %#08lx", stackframe->rip);
		stackframe = stackframe->rbp;
	}
}

void dump_interrupt_frame(interrupt_frame_t* frame)
{
	printf(" CS: %#08lx RIP: %#08lx EFL: %#08lx\n", frame->cs, frame->ip, frame->flags);

	printf(" RAX: %#08lx RBX: %#08lx RCX: %#08lx RDX: %#08lx\n", frame->rax, frame->rbx, frame->rcx,
		   frame->rdx);

	printf(" RSI: %#08lx RDI: %#08lx RBP: %#08lx RSP: %#08lx\n", frame->rsi, frame->rdi, frame->rbp,
		   frame->user_sp);

	printf("  R8: %#08lx  R9: %#08lx R10: %#08lx R11: %#08lx\n", frame->r8, frame->r9, frame->r10,
		   frame->r11);

	printf(" R12: %#08lx R13: %#08lx R14: %#08lx R15: %#08lx\n", frame->r12, frame->r13, frame->r14,
		   frame->r15);

	printf(" ERRC: %#08lx\n", frame->err_code);
}

void error_handler(interrupt_frame_t* frame)
{
	LOG_ERROR("Exception(%s) occurred", interrupt_exception_messages[frame->vector]);

	dump_interrupt_frame(frame);

	if(frame->rbp != 0)
	{
		LOG_ERROR("Stacktrace: ");
		dump_backtrace(frame->rbp);
	}

	LOG_FATAL("Halting System!");
}

void exception_handler(interrupt_frame_t* frame)
{
	if(frame->vector < 0x20)
	{
		error_handler(frame);
	}

	LOG_FATAL("Called interrupt");
}