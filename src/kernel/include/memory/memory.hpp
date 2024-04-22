#ifndef MEMORY_MEMORY_HPP
#define MEMORY_MEMORY_HPP

#include <stddef.h>

#define PAGE_SIZE 0x1000

constexpr inline size_t bytes_to_kb(size_t bytes) {
	return bytes / 1024;
}

constexpr inline size_t bytes_to_mb(size_t bytes) {
	return bytes_to_kb(bytes) / 1024;
}

constexpr inline size_t bytes_to_gb(size_t bytes) {
	return bytes_to_mb(bytes) / 1024;
}

namespace memory {
void init();
}  // namespace memory

#endif	// MEMORY_MEMORY_HPP