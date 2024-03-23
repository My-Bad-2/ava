#include <log.h>
#include <memory/memory.h>
#include <memory/phys.h>
#include <libs/bitmap.h>
#include <string.h>
#include <libs/utils.h>

bitmap_t phys_bitmap = {};

size_t pmm_last_index = 0;
size_t pmm_phys_page_size = 0;
size_t pmm_usable_memory = 0;
size_t pmm_total_memory = 0;
size_t pmm_used_memory = 0;
uintptr_t pmm_highest_usable_memory = 0;

void* internal_pmm_alloc_page(size_t limit, size_t count)
{
	size_t i = 0;

	while(pmm_last_index < limit)
	{
		if(!bitmap_get(&phys_bitmap, pmm_last_index++))
		{
			if(++i == count)
			{
				size_t page = pmm_last_index - count;

				for(size_t j = page; j < pmm_last_index; ++j)
				{
					bitmap_set(&phys_bitmap, j, true);
				}

				return (void*)(page * PAGE_SIZE);
			}
		}
		else
		{
			i = 0;
		}
	}

	return NULL;
}

void* pmm_alloc_pages(size_t count)
{
	if(count == 0)
	{
		return NULL;
	}

	size_t i = pmm_last_index;
	void* ret = internal_pmm_alloc_page(pmm_highest_usable_memory / PAGE_SIZE, count);

	if(ret == NULL)
	{
		pmm_last_index = 0;
		ret = internal_pmm_alloc_page(i, count);

		if(ret == NULL)
		{
			LOG_FATAL("Out of usable Physical Memory!");
		}
	}

	memset(TO_HIGHER_HALF(ret), 0, count * PAGE_SIZE);
	pmm_used_memory += (count * PAGE_SIZE);

	return ret;
}

void* pmm_alloc_page(void)
{
	return pmm_alloc_pages(1);
}

void pmm_free_pages(void* address, size_t count)
{
	if(address == NULL)
	{
		LOG_DEBUG("Address passed is NULL!");
		return;
	}

	size_t page = (uintptr_t)(address) / PAGE_SIZE;

	for(size_t i = page; i < (page + count); ++i)
	{
		bitmap_set(&phys_bitmap, i, false);
	}

	pmm_used_memory -= count * PAGE_SIZE;
}

void pmm_free_page(void* address)
{
	return pmm_free_pages(address, 1);
}

void pmm_init(void)
{
	const size_t count = memmap_request.response->entry_count;
	struct limine_memmap_entry** entries = memmap_request.response->entries;

	uintptr_t top_memory = 0;

	for(size_t i = 0; i < count; ++i)
	{
		uintptr_t top = entries[i]->base + entries[i]->length;
		top_memory = GET_MAX(top_memory, top);

		switch(entries[i]->type)
		{
			case LIMINE_MEMMAP_USABLE:
				pmm_usable_memory += entries[i]->length;
				pmm_highest_usable_memory = GET_MAX(pmm_highest_usable_memory, top);
				break;
			case LIMINE_MEMMAP_KERNEL_AND_MODULES:
			case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
				pmm_used_memory += entries[i]->length;
				break;
			default:
				continue;
		}

		pmm_total_memory += entries[i]->length;
	}

	size_t bitmap_entries = pmm_highest_usable_memory / PAGE_SIZE;
	size_t bitmap_size = ALIGN_UP(bitmap_entries / sizeof(uint8_t), PAGE_SIZE);
	bitmap_entries = bitmap_size * 8;

	for(size_t i = 0; i < count; ++i)
	{
		if(entries[i]->type != LIMINE_MEMMAP_USABLE)
		{
			continue;
		}

		if(entries[i]->length >= bitmap_size)
		{
			bitmap_init(&phys_bitmap, (uint8_t*)(entries[i]->base), bitmap_entries);
			bitmap_fill(&phys_bitmap, true);

			entries[i]->length -= bitmap_size;
			entries[i]->base += bitmap_size;

			pmm_used_memory += bitmap_size;

			break;
		}
	}

	for(size_t i = 0; i < count; ++i)
	{
		if(entries[i]->type != LIMINE_MEMMAP_USABLE)
		{
			continue;
		}

		for(uintptr_t j = 0; j < entries[i]->length; j += PAGE_SIZE)
		{
			bitmap_set(&phys_bitmap, (entries[i]->base + j) / PAGE_SIZE, false);
		}
	}

	LOG_INFO("Initialized Physical Memory Manager!");
	pmm_print_data();
}

void pmm_print_data(void)
{
	printf("\tTotal Memory(in MB): %lu\n", BYTES_TO_MEGABYTES(pmm_total_memory));
	printf("\tUsed Memory (in MB): %lu\n", BYTES_TO_MEGABYTES(pmm_used_memory));
	printf("\tFree Memory (in MB): %lu\n", BYTES_TO_MEGABYTES(pmm_total_memory - pmm_used_memory));
}