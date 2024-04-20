#ifndef LOG_HPP
#define LOG_HPP

#include <array>
#include <source_location>
#include <stdio.h>

#define LEVEL_PREFIX                                                           \
	{ "<T> ", "<D> ", "<I> ", "<W> ", "<E> ", "<!> " }

#define LOG_TRACE(fmt, ...)                                                    \
	global_logger()->trace(std::source_location::current(), fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)                                                    \
	global_logger()->debug(std::source_location::current(), fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)                                                     \
	global_logger()->info(std::source_location::current(), fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)                                                     \
	global_logger()->warn(std::source_location::current(), fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)                                                    \
	global_logger()->error(std::source_location::current(), fmt, ##__VA_ARGS__)
#define LOG_CRITICAL(fmt, ...)                                                 \
	global_logger()->critical(std::source_location::current(), fmt,            \
							  ##__VA_ARGS__)

enum log_levels {
	LOG_LEVEL_TRACE,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_CRITICAL,
	LOG_LEVEL_COUNT,
};

class logger_base {
   public:
	logger_base() : stream(stderr), level_prefix(LEVEL_PREFIX) {}

	constexpr logger_base(FILE* stream)
		: stream(stream), level_prefix(LEVEL_PREFIX) {}

	template <typename... Args>
	void trace(std::source_location location, const char* format,
			   Args&&... args) {
		log(LOG_LEVEL_TRACE, location, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void debug(std::source_location location, const char* format,
			   Args&&... args) {
		log(LOG_LEVEL_DEBUG, location, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void info(std::source_location location, const char* format,
			  Args&&... args) {
		log(LOG_LEVEL_INFO, location, format, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void warn(std::source_location location, const char* format,
			  Args&&... args) {
		this->log(LOG_LEVEL_WARN, location, format,
				  std::forward<Args>(args)...);
	}

	template <typename... Args>
	void error(std::source_location location, const char* format,
			   Args&&... args) {
		this->log(LOG_LEVEL_ERROR, location, format,
				  std::forward<Args>(args)...);
	}

	template <typename... Args>
	void critical(std::source_location location, const char* format,
				  Args&&... args) {
		this->log(LOG_LEVEL_CRITICAL, location, format,
				  std::forward<Args>(args)...);
	}

   private:
	void log(log_levels level, std::source_location location,
			 const char* format, ...);
	const char* get_level_color(log_levels level);

	FILE* stream;
	std::array<const char*, LOG_LEVEL_COUNT> level_prefix;
};

logger_base* global_logger();

#endif	// LOG_HPP