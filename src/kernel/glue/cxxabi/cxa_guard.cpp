#include <glue/cxxabi.h>
#include <log.hpp>

namespace __cxxabiv1 {
int __cxa_guard_acquire(uint64_t* guard) {
	if ((*guard) & 0x0001) {
		return 0;
	}

	if ((*guard) & 0x0100) {
		LOG_CRITICAL("ABORT!");
	}

	*guard |= 0x0100;
	return 1;
}

void __cxa_guard_release(uint64_t* guard) {
	*guard |= 0x0001;
}

void __cxa_guard_abort(uint64_t* guard) {
	LOG_CRITICAL("__cxa_guard_abort(%p)", static_cast<void*>(guard));
}
}  // namespace __cxxabiv1