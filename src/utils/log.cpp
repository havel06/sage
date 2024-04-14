#include "log.hpp"
#include <stdarg.h>
#include <stdio.h>

const char* log_level_str(Log_Level level)
{
	switch (level) {
		case Log_Level::debug:
			return "DEBUG";
		case Log_Level::error:
			return "ERROR";
		case Log_Level::info:
			return "INFO";
		case Log_Level::warning:
			return "WARNING";
	}
}

void log_message(Log_Level level, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stdout, "[%s] ", log_level_str(level));
	vfprintf(stdout, fmt, args);
	fputs("\n", stdout);
	va_end(args);
}
