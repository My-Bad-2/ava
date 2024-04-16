#include <limine.h>

extern "C" void kmain() {
    for (;;) {
        asm volatile("hlt");
    }
}