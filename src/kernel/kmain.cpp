#include <limine.h>
#include <arch.hpp>

extern "C" void kmain() {
    for (;;) {
        arch::pause();
    }
}