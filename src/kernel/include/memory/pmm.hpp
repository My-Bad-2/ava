#ifndef MEMORY_PMM_H
#define MEMORY_PMM_H

#include <stddef.h>
#include <sys/cdefs.h>

namespace memory {
void* phys_alloc_page(size_t count = 1);
void phys_free_page(void* ptr, size_t count);

void phys_init();
void phys_print_stats();

template <typename T = void*>
inline T phys_alloc_page(size_t count = 1) {
	return reinterpret_cast<T>(phys_alloc_page(count));
}

inline void phys_free_page(auto ptr, size_t count = 1) {
	return phys_free_page(reinterpret_cast<void*>(ptr), count);
}
}  // namespace memory

#endif	// MEMORY_PMM_H