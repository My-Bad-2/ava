#ifndef GLUE_CXXABI_H
#define GLUE_CXXABI_H

#include <stdint.h>
#include <sys/cdefs.h>

namespace __cxxabiv1 {
extern "C" {
extern __EXPORT __COLD int __cxa_guard_acquire(uint64_t* guard);
extern __EXPORT __COLD void __cxa_guard_release(uint64_t* guard);
extern __EXPORT __COLD void __cxa_guard_abort(uint64_t* guard);
}
}  // namespace __cxxabiv1

#endif	// GLUE_CXXABI_H