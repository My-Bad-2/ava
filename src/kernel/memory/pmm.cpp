#include <algorithm>

#include <kernel.hpp>
#include <log.hpp>

#include <memory/memory.hpp>
#include <memory/pmm.hpp>

#include <utils/bitmap.hpp>
#include <utils/misc.hpp>

namespace memory {
namespace {
bitmap_t<uint8_t> phys_bitmap;

size_t phys_last_index = 0;
size_t phys_usable_memory = 0;
size_t phys_total_memory = 0;
size_t phys_used_memory = 0;

uintptr_t phys_highest_usable_memory = 0;
}  // namespace

void* phys_alloc_page(size_t count) {
	if (count == 0) {
		return nullptr;
	}

	auto inner_alloc = [count](size_t limit) -> void* {
		size_t i = 0;

		while (phys_last_index < limit) {
			if (!phys_bitmap[phys_last_index++]) {
				if (++i == count) {
					size_t page = phys_last_index - count;

					for (size_t j = page; j < phys_last_index; j++) {
						phys_bitmap[i] = true;
					}

					return reinterpret_cast<void*>(page * PAGE_SIZE);
				}
			} else {
				i = 0;
			}
		}

		return nullptr;
	};

	size_t i = phys_last_index;
	void* ret = inner_alloc(phys_highest_usable_memory / PAGE_SIZE);

	if (ret == nullptr) {
		phys_last_index = 0;
		ret = inner_alloc(i);

		if (ret == nullptr) {
			LOG_CRITICAL("Out of Memory!");
		}
	}

	memset(to_higher_half(ret), 0, count * PAGE_SIZE);
	phys_used_memory += count * PAGE_SIZE;

	return ret;
}

void phys_free_page(void* ptr, size_t count = 1) {
	if (ptr == nullptr) {
		return;
	}

	size_t page = reinterpret_cast<size_t>(ptr) / PAGE_SIZE;

	for (size_t i = page; i < (page + count); ++i) {
		phys_bitmap[i] = false;
	}

	phys_used_memory -= count * PAGE_SIZE;
}

void phys_print_stats() {
	printf("\tTotal Memory: %lu MB.\n", bytes_to_mb(phys_total_memory));
	printf("\tUsed  Memory: %lu MB.\n", bytes_to_mb(phys_used_memory));
	printf("\tFree  Memory: %lu MB.\n",
		   bytes_to_mb(phys_total_memory - phys_used_memory));
}

void phys_init() {
	limine_memmap_entry** memmaps = memmap_request.response->entries;
	size_t count = memmap_request.response->entry_count;

	for (size_t i = 0; i < count; ++i) {
		uintptr_t highest_addr = memmaps[i]->base + memmaps[i]->length;

		switch (memmaps[i]->type) {
			case LIMINE_MEMMAP_USABLE:
				phys_usable_memory += memmaps[i]->length;
				phys_highest_usable_memory =
					std::max(phys_highest_usable_memory, highest_addr);
				break;
			case LIMINE_MEMMAP_KERNEL_AND_MODULES:
			case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
				phys_used_memory += memmaps[i]->length;
				break;
			default:
				continue;
		}

		phys_total_memory += memmaps[i]->length;
	}

	size_t bitmap_entries = phys_highest_usable_memory / PAGE_SIZE;
	size_t bitmap_size = align_up(bitmap_entries / 8, PAGE_SIZE);
	bitmap_entries = bitmap_size * 8;

	for (size_t i = 0; i < count; ++i) {
		if (memmaps[i]->type != LIMINE_MEMMAP_USABLE) {
			continue;
		}

		if (memmaps[i]->length >= bitmap_size) {
			phys_bitmap.init(
				reinterpret_cast<uint8_t*>(to_higher_half(memmaps[i]->base)),
				bitmap_entries);
			phys_bitmap.fill(0xFF);

			memmaps[i]->base += bitmap_size;
			memmaps[i]->length -= bitmap_size;

			phys_used_memory += bitmap_size;
			break;
		}
	}

	for (size_t i = 0; i < count; ++i) {
		if (memmaps[i]->type != LIMINE_MEMMAP_USABLE) {
			continue;
		}

		for (uintptr_t j = 0; j < memmaps[i]->length; j += PAGE_SIZE) {
			phys_bitmap[(memmaps[i]->base + j) / PAGE_SIZE] = false;
		}
	}

	LOG_INFO("Initialized Physical Memory Manager.");
	phys_print_stats();
}
}  // namespace memory