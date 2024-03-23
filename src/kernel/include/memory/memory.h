#ifndef KERNEL_INCLUDE_MEMORY_MEMORY_H
#define KERNEL_INCLUDE_MEMORY_MEMORY_H

#include <kernel.h>

#define IS_HIGHER_HALF(address) ((uintptr_t)(address) >= get_hhdm_offset())

#define TO_HIGHER_HALF(address)                             \
	(IS_HIGHER_HALF(address) ? ((typeof(address))(address)) : \
							   ((typeof(address))((uintptr_t)(address) + get_hhdm_offset())))

#define FROM_HIGHER_HALF(address)                           \
	(IS_HIGHER_HALF(address) ? ((typeof(address))(address)) : \
							   ((typeof(address))((uintptr_t)(address)-get_hhdm_offset())))

#define ALIGN_DOWN(a, b) ((a) & ~((b) - (1)))
#define ALIGN_UP(a, b) ALIGN_DOWN((a) + (b) - (1), b)
#define DIV_ROUNDUP(a, b) ALIGN_UP((a), (b)) / (b)

#define BYTES_TO_MEGABYTES(bytes) ((bytes) / 1024 / 1024)
#define BYTES_TO_GIGABYTES(bytes) ((BYTES_TO_MEGABYTES) / 1024)

#define PAGE_SIZE 0x1000
#define PAGE_SHIFT 12
#define PAGE_MASK (~(PAGE_SIZE - 1))

#endif // KERNEL_INCLUDE_MEMORY_MEMORY_H