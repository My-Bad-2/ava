.text
.global idt_update
idt_update:
    lidt (%rdi)
    retq