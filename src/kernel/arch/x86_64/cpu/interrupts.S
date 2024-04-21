.macro ISR number
interrupt_\number:
.if !(\number == 8 || (\number >= 10 && \number <= 14) || \number == 17 || \number == 21 || \number == 29 || \number == 30)
    push 0
.endif
    pushq $\number
    jmp interrupt_common
.endm

.altmacro
.macro ISR_INSERT number
    .quad interrupt_\number
.endm

.section .text

# TODO: Handle Non-maskable interrupts & Interrupts from userspace.
.extern interrupt_handler
interrupt_common:
    # Clear the direction flag. Without this, uses of string instructions, e.g.
    # REP MOVS in memcpy() or inline by the compiler, can go wrong and copy in
    # the wrong direction, since this code may assume that the direction flag
    # is unset
    cld

    # Save General purpose registers
    pushq %rax
    pushq %rbx
    pushq %rcx
    pushq %rdx
    pushq %rsi
    pushq %rdi
    pushq %rbp
    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    # At this point the stack contains the complete interrupt frame
    movq %rsp, %rdi # Pass the interrupt frame in rdi

    # Here the call should split into two paths, one for NMI interrupts
    # other for non-NMI interrupts.

    # Before calling interrupt handler, don't forget to swap gs base
    # to kernel-space from userspace
    call interrupt_handler

    # Common interrupt exit starts here
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8
    popq %rbp
    popq %rdi
    popq %rsi
    popq %rdx
    popq %rcx
    popq %rbx
    popq %rax

    # Drop vector number and error code
    add $16, %rsp

    # Return from interrupt
    iretq

.set i, 0
.rept 256
    ISR %i
.set i, i + 1
.endr

.section .data
.global __interrupt_vector
__interrupt_vector:
.set i, 0
.rept 256
    ISR_INSERT %i
.set i, i + 1
.endr