#ifndef KERNEL_INCLUDE_LIBS_BITMAP_H
#define KERNEL_INCLUDE_LIBS_BITMAP_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct
{
	uint8_t* data;
	size_t size;
} bitmap_t;

bool bitmap_get(const bitmap_t* bitmap, size_t index);
void bitmap_set(const bitmap_t* bitmap, size_t index, bool value);
void bitmap_init(bitmap_t* self, void* data, size_t size);
size_t bitmap_len(const bitmap_t* bitmap);
void bitmap_fill(bitmap_t* bitmap, bool value);

#endif // KERNEL_INCLUDE_LIBS_BITMAP_H