.text

.global gdt_update
gdt_update:
    lgdtq (%rdi)
    movw $0x10, %ax
    movl %eax, %ds
    movl %eax, %es
    movl %eax, %fs
    movl %eax, %gs
    movl %eax, %ss
    movabsq $.gdt_trampoline, %rax
    pushq $0x8
    pushq %rax
    lretq

.gdt_trampoline:
    retq

.global tss_update
tss_update:
    movw $0x28, %ax
    ltrw %ax
    retq