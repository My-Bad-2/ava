#ifndef UTILS_BITMAP_HPP
#define UTILS_BITMAP_HPP

#include <string.h>

#define BIT_SIZE(T) (sizeof(T) * 8)

template <typename T>
class bitmap_t {
   private:
	T* buffer;
	size_t size;
	bool initialized;

   public:
	constexpr bitmap_t() = default;

	constexpr bitmap_t(T* buffer, size_t size)
		: buffer(buffer), size(size), initialized(true) {}

	constexpr ~bitmap_t() = default;

	void init(T* buffer, size_t size) {
		this->buffer = buffer;
		this->size = size;
		this->initialized = true;
	}

	void fill(T value) { memset(this->buffer, value, this->size); }

	constexpr bool get(size_t index) {
		return this->buffer[index / BIT_SIZE(T)] & (1 << (index % BIT_SIZE(T)));
	}

	constexpr bool set(size_t index, bool value) {
		bool ret = this->get(index);

		if (value) {
			this->buffer[index / BIT_SIZE(T)] |= (1 << (index % BIT_SIZE(T)));
		} else {
			this->buffer[index / BIT_SIZE(T)] &= ~(1 << (index % BIT_SIZE(T)));
		}

		return ret;
	}

	constexpr size_t length() const { return this->size; }

	constexpr T* data() const { return this->buffer; }

	struct bit {
		bitmap_t& parent;
		size_t index;

		constexpr bit(bitmap_t& parent, size_t index)
			: parent(parent), index(index) {}

		constexpr void operator=(bool value) {
			this->parent.set(this->index, value);
		}

		constexpr operator bool() const {
			return this->parent.get(this->index);
		}
	};

	constexpr bit operator[](size_t index) { return bit(*this, index); }
};

#endif	// UTILS_BITMAP_HPP