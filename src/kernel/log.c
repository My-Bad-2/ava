#include <arch.h>
#include <log.h>
#include <stdarg.h>
#include <stdbool.h>

#define LOG_COLOR_RED "\033[0;31m"
#define LOG_COLOR_GREEN "\033[0;32m"
#define LOG_COLOR_YELLOW "\033[0;33m"
#define LOG_COLOR_BLUE "\033[0;34m"
#define LOG_COLOR_CYAN "\033[0;35m"
#define LOG_COLOR_RESET "\033[0m"

FILE* log_output_stream = NULL;
bool log_initialized = false;

int log_set_stream(FILE* fp)
{
	if(log_initialized)
	{
		return false;
	}

	if(fp == 0)
	{
		fp = stdout;
	}

	log_output_stream = fp;
	log_initialized = true;

	return true;
}

static char log_get_level_char(log_level level)
{
	switch(level)
	{
		case Log_level_Trace:
			return 'T';
		case Log_level_Debug:
			return 'D';
		case Log_level_Info:
			return 'I';
		case Log_level_Warn:
			return 'W';
		case Log_level_Error:
			return 'E';
		case Log_level_Fatal:
			return 'F';
		default:
			return ' ';
	}
}

static const char* log_get_level_color(log_level level)
{
	switch(level)
	{
		case Log_level_Trace:
			return LOG_COLOR_BLUE;
		case Log_level_Debug:
			return LOG_COLOR_CYAN;
		case Log_level_Info:
			return LOG_COLOR_GREEN;
		case Log_level_Warn:
			return LOG_COLOR_YELLOW;
		case Log_level_Error:
		case Log_level_Fatal:
			return LOG_COLOR_RED;
	}
}

static void vlog_message(FILE* fp, char level_char, const char* level_color, const char* file,
						 int line, const char* fmt, va_list args)
{
	fprintf(fp, "%s[%c]%s ", level_color, level_char, LOG_COLOR_RESET);
	fprintf(fp, "%s %d: %s", file, line, level_color);

	vfprintf(fp, fmt, args);

	fprintf(fp, "%s\n", LOG_COLOR_RESET);
}

void log_message(log_level level, const char* file, int line, const char* fmt, ...)
{
	if(!log_initialized)
	{
		return;
	}

	char level_char = log_get_level_char(level);
	const char* level_color = log_get_level_color(level);

	va_list args;

	va_start(args, fmt);
	vlog_message(log_output_stream, level_char, level_color, file, line, fmt, args);
	va_end(args);

	if(level == Log_level_Fatal)
	{
		while(true)
		{
			arch_disable_interrupts();
			arch_halt();
		}
	}
}