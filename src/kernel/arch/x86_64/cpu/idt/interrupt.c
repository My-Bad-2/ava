#include <log.h>
#include <stdint.h>

void exception_handler(uint64_t print)
{
	(void)print;
	LOG_FATAL("Called interrupt");
}