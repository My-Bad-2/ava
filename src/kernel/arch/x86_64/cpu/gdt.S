#define NULL_SELECTOR (0x00)
#define KERNEL_CODE_SELECTOR (0x08)
#define KERNEL_DATA_SELECTOR (0x10)
#define USER_DATA_SELECTOR (0x18 | 3)
#define USER_CODE_SELECTOR (0x20 | 3)
#define TSS_SELECTOR (0x28)

.section .text

.global gdt_update
gdt_update:
    lgdtq (%rdi)
    movw $KERNEL_DATA_SELECTOR, %ax
    movl %eax, %ds
    movl %eax, %fs
    movl %eax, %gs
    movl %eax, %es
    movl %eax, %ss
    pushq $KERNEL_CODE_SELECTOR
    lea .gdt_trampoline(%rip), %rax
    pushq %rax
    lretq
.gdt_trampoline:
    retq

.global tss_update
tss_update:
    movw $TSS_SELECTOR, %ax
    ltrw %ax
    retq