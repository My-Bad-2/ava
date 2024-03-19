#ifndef KERNEL_INCLUDE_LOG_H
#define KERNEL_INCLUDE_LOG_H

#include <stdio.h>

#define LOG_TRACE(fmt, ...) log_message(Log_level_Trace, __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) log_message(Log_level_Debug, __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) log_message(Log_level_Info, __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) log_message(Log_level_Warn, __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_message(Log_level_Error, __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) log_message(Log_level_Fatal, __FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__)

__BEGIN_DECLS

typedef enum
{
	Log_level_Trace,
	Log_level_Debug,
	Log_level_Info,
	Log_level_Warn,
	Log_level_Error,
	Log_level_Fatal,
} log_level;

int log_set_stream(FILE* fp);
void log_message(log_level level, const char* file, int line, const char* fmt, ...) __PRINTFLIKE(4, 5);

__END_DECLS

#endif // KERNEL_INCLUDE_LOG_H