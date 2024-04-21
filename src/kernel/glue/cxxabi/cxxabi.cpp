#include <glue/cxxabi.h>

namespace __cxxabiv1 {
namespace {
extern "C" void (*__init_array_start[])();
extern "C" void (*__init_array_end[])();
}  // namespace

void init() {
	for (void (**ctor)() = __init_array_start; ctor < __init_array_end;
		 ctor++) {
		(*ctor)();
	}
}
}  // namespace __cxxabiv1