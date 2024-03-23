#ifndef KERNEL_INCLUDE_KERNEL_H
#define KERNEL_INCLUDE_KERNEL_H

#include <limine.h>
#include <sys/features.h>

#ifndef PROJECT_NAME
	#define PROJECT_NAME "Ava-default"
#endif

#ifndef PROJECT_VERSION
	#define PROJECT_VERSION "1.0.0"
#endif

extern volatile struct limine_memmap_request memmap_request;
extern volatile struct limine_hhdm_request hhdm_request;

uintptr_t get_hhdm_offset();

#endif // KERNEL_INCLUDE_KERNEL_H