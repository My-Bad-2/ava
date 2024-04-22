#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <limine.h>

extern volatile limine_hhdm_request hhdm_request;
extern volatile limine_memmap_request memmap_request;

inline uintptr_t hhdm_offset() {
    return hhdm_request.response->offset;
}

#endif	// KERNEL_HPP