#ifndef UTILS_MISC_HPP
#define UTILS_MISC_HPP

#include <stdint.h>
#include <type_traits>
#include <concepts>

extern uintptr_t hhdm_offset();

template <typename T>
using get_return_t = std::conditional_t<
	std::integral<T>,
	std::conditional_t<std::unsigned_integral<T>, uintptr_t, intptr_t>, T>;

inline constexpr bool is_higher_half(auto a) {
	return uintptr_t(a) >= hhdm_offset();
}

template <typename T, typename Ret = get_return_t<T>>
inline constexpr Ret to_higher_half(T address) {
	return is_higher_half(address) ? Ret(address)
								   : Ret(uintptr_t(address) + hhdm_offset());
}

template <typename T, typename Ret = get_return_t<T>>
inline constexpr Ret from_higher_half(T address) {
	return !is_higher_half(address) ? Ret(address)
									: Ret(uintptr_t(address) - hhdm_offset());
}

template <std::integral T1, std::integral T2>
constexpr auto align_down(T1 a, T2 b) {
	constexpr auto align_down_internal = [&](auto a, auto b) {
		return (a & ~(b - 1));
	};

	return align_down_internal(std::make_unsigned_t<T1>(a),
							   std::make_unsigned_t<T2>(b));
}

template <std::integral T1, std::integral T2>
constexpr auto align_up(T1 a, T2 b) {
	return align_down(a + b - 1, b);
}

template <std::integral T1, std::integral T2>
constexpr auto div_roundup(T1 a, T2 b) {
	return align_down(a + b - 1, b) / b;
}

#endif	// UTILS_MISC_HPP