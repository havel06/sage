#include "log.hpp"
#include <stdarg.h>
#include <stdio.h>

const char* log_level_str(Log_Level level)
{
	switch (level) {
		case Log_Level::debug:
			return "\033[96mDEBUG\033[39m";
		case Log_Level::error:
			return "\033[91mERROR\033[39m";
		case Log_Level::info:
			return "\033[92mINFO\033[39m";
		case Log_Level::warning:
			return "\033[93mWARNING\033[39m";
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
