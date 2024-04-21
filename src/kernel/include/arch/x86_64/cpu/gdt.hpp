/// \file gdt.hpp
/// \author My-Bad-2
/// \brief Global Descriptor Table & Task State Segment
/// \version 0.1
/// \date 2024-04-21
///
/// \copyright MIT - Copyright (c) 2024

#ifndef ARCH_CPU_GDT_HPP
#define ARCH_CPU_GDT_HPP

#include <stdint.h>
#include <sys/cdefs.h>

#define NULL_SELECTOR (0x00)
#define KERNEL_CODE_SELECTOR (0x08)
#define KERNEL_DATA_SELECTOR (0x10)
#define USER_DATA_SELECTOR (0x18 | 3)
#define USER_CODE_SELECTOR (0x20 | 3)
#define TSS_SELECTOR (0x28)

namespace arch::cpu {
/// \struct gdt_entry_t
///
/// \brief Structure representing an entry in the x86_64 Global Descriptor Table.
struct gdt_entry_t {
	uint16_t limit0_15;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t flags;
	uint8_t limit16_19 : 4;
	uint8_t granularity : 4;
	uint8_t base24_31;

	constexpr gdt_entry_t() = default;

	/// \brief Initializes the GDT entry with the specified parameters.
	///
	/// \param base The base address of the segment
	/// \param limit The limit of the segment
	/// \param granularity The granularity of the segment
	/// \param flags The flags associated with the segment
	constexpr gdt_entry_t(uint32_t base, uint32_t limit, uint8_t granularity,
						  uint8_t flags)
		: limit0_15(static_cast<uint16_t>(limit & 0xFFFF)),
		  base0_15(static_cast<uint16_t>(base & 0xFFFF)),
		  base16_23(static_cast<uint8_t>((base >> 16) & 0xFF)), flags(flags),
		  limit16_19((limit >> 16) & 0x0F), granularity(granularity),
		  base24_31(static_cast<uint8_t>((base >> 24) & 0xFF)) {}
} __PACKED;

/// \struct tss_t
///
/// \brief Structure representing an x86_64 TSS (Task State Segment).
struct tss_t {
	uint32_t reserved;
	uint64_t rsp[3];
	uint64_t reserved0;
	uint64_t ist[7];
	uint32_t reserved1;
	uint32_t reserved2;
	uint16_t reserved3;
	uint16_t iopb_offset;

	constexpr tss_t() = default;
} __PACKED;

/// \struct tss_entry_t
///
/// \brief Structure represeniting a TSS entry in the global Descriptor Table.
struct tss_entry_t {
	uint16_t len;
	uint16_t base0_15;
	uint8_t base16_23;
	uint8_t flags1;
	uint8_t flags2;
	uint8_t base_high24_31;
	uint32_t base_upper32_64;
	uint32_t reserved;

	constexpr tss_entry_t() = default;

	/// \brief Initializes Task State Segment entry with the specified TSS.
	///
	/// \param tss Pointer to the TSS structure.
	tss_entry_t(void* tss)
		: len(sizeof(tss_t)),
		  base0_15(reinterpret_cast<uintptr_t>(tss) & 0xFFFF),
		  base16_23((reinterpret_cast<uintptr_t>(tss) >> 16) & 0xFF),
		  flags1(0x89), flags2(0),
		  base_high24_31((reinterpret_cast<uintptr_t>(tss) >> 24) & 0xFF),
		  base_upper32_64(reinterpret_cast<uintptr_t>(tss) >> 32), reserved(0) {
	}
} __PACKED;

/// \struct gdt_descriptor_t
///
/// \brief Structure representing the GDT register.
struct gdt_descriptor_t {
	uint16_t limit;
	uint64_t base;

	constexpr gdt_descriptor_t() = default;

	constexpr gdt_descriptor_t(uint16_t limit, uint64_t base)
		: limit(limit), base(base) {}

	/// \brief Loads the Global Descriptor Table & Task State Segment.
	void flush();
} __PACKED;

/// \struct gdt_t
///
/// \brief Structure representing the Global Descriptor Table.
struct gdt_t {
	gdt_entry_t null;
	gdt_entry_t kernel_code;
	gdt_entry_t kernel_data;
	gdt_entry_t user_data;
	gdt_entry_t user_code;
	tss_entry_t tss;
} __PACKED;

/// \brief Initialize the Global Descriptor Table.
void init_gdt();
}  // namespace arch::cpu

#endif	// ARCH_CPU_GDT_HPP