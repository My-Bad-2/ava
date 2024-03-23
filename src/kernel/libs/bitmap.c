#include <libs/bitmap.h>
#include <stdint.h>
#include <string.h>

#define BITS_BYTE_INDEX(index) ((index) / (sizeof(uint8_t) * 8))
#define BITS_BIT_INDEX(index) ((index) % (sizeof(uint8_t) * 8))

bool bitmap_get(const bitmap_t* bitmap, size_t index)
{
	const size_t byte_index = BITS_BYTE_INDEX(index);
	const size_t bit_index = BITS_BIT_INDEX(index);

	return bitmap->data[byte_index] & (1 << bit_index);
}

void bitmap_set(const bitmap_t* bitmap, size_t index, bool value)
{
	const size_t byte_index = BITS_BYTE_INDEX(index);
	const size_t bit_index = BITS_BIT_INDEX(index);

	if(value)
	{
		bitmap->data[byte_index] |= 1 << bit_index;
	}
	else
	{
		bitmap->data[byte_index] &= ~(1 << bit_index);
	}
}

void bitmap_init(bitmap_t* self, void* data, size_t size)
{
	self->data = data;
	self->size = size;
}

size_t bitmap_len(const bitmap_t* bitmap)
{
	return bitmap->size * (sizeof(uint8_t) * 8);
}

void bitmap_fill(bitmap_t* bitmap, bool value)
{
	if(value)
	{
		memset(bitmap->data, 0xFF, bitmap->size);
	}
	else
	{
		memset(bitmap->data, 0, bitmap->size);
	}
}