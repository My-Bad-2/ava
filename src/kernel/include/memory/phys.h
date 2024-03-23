#ifndef KERNEL_INCLUDE_MEMORY_PHYS_H
#define KERNEL_INCLUDE_MEMORY_PHYS_H

#include <stddef.h>
#include <stdbool.h>

void* pmm_alloc_pages(size_t count);
void* pmm_alloc_page(void);

void pmm_free_pages(void* address, size_t count);
void pmm_free_page(void* address);

void pmm_init(void);
void pmm_print_data(void);

#endif // KERNEL_INCLUDE_MEMORY_PHYS_H