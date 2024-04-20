#include <arch.hpp>
#include <log.hpp>
#include <string.h>
#include <utility>

#define GET_FILENAME(filename)                                                 \
	(strrchr(filename, '/') ? strrchr(filename, '/') + 1 : filename)

#define LOG_COLOR_RED "\033[0;31m"
#define LOG_COLOR_GREEN "\033[0;32m"
#define LOG_COLOR_YELLOW "\033[0;33m"
#define LOG_COLOR_BLUE "\033[0;34m"
#define LOG_COLOR_CYAN "\033[0;35m"
#define LOG_COLOR_RESET "\033[0m"

namespace {
logger_base* glogger = nullptr;

void log_msg(FILE* stream, const char* prefix, const char* color,
			 std::source_location location, const char* format, va_list args) {
	fprintf(stream, "%s%s%s", color, prefix, LOG_COLOR_RESET);
	fprintf(stream, "%s%s [%d, %s]: %s", LOG_COLOR_YELLOW, GET_FILENAME(location.file_name()),
			location.line(), location.function_name(), color);

	vfprintf(stream, format, args);

	fprintf(stream, "%s\n", LOG_COLOR_RESET);
}
}  // namespace

const char* logger_base::get_level_color(log_levels level) {
	switch (level) {
		case LOG_LEVEL_TRACE:
			return LOG_COLOR_BLUE;
		case LOG_LEVEL_DEBUG:
			return LOG_COLOR_CYAN;
		case LOG_LEVEL_INFO:
			return LOG_COLOR_GREEN;
		case LOG_LEVEL_WARN:
			return LOG_COLOR_YELLOW;
		case LOG_LEVEL_ERROR:
		case LOG_LEVEL_CRITICAL:
			return LOG_COLOR_RED;
		default:
			return nullptr;
	}
}

void logger_base::log(log_levels level, std::source_location location,
					  const char* format, ...) {
	if (level == LOG_LEVEL_COUNT) {
		return;
	}

	const char* prefix = level_prefix[std::to_underlying(level)];
	const char* color = this->get_level_color(level);

	va_list args;

	va_start(args, format);
	log_msg(stream, prefix, color, location, format, args);
	va_end(args);

	if (level == LOG_LEVEL_CRITICAL) {
		while (true) {
			arch::disable_interrupts();
			arch::halt();
		}
	}
}

logger_base* global_logger() {
	if (glogger == nullptr) {
		static logger_base logger = {};
		glogger = &logger;
	}

	return glogger;
}