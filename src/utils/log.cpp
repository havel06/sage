#include "log.hpp"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "utils/array.hpp"

static int log_level = (int)Log_Level::debug;
static Array<Log_Observer*> observers = {};

void set_log_level(Log_Level level)
{
	log_level = (int)level;
}

void log_add_observer(Log_Observer& observer)
{
	observers.push_back(&observer);
}

void log_remove_observer(Log_Observer& observer)
{
	for (int i = 0; i < observers.size(); i++) {
		if (observers[i] == &observer) {
			observers.remove(i);
			return;
		}
	}
}

Log_Level log_level_from_string(const char* str, Log_Level fallback)
{
	if (strcmp(str, "debug") == 0) {
		return Log_Level::debug;
	}

	if (strcmp(str, "info") == 0) {
		return Log_Level::info;
	}

	if (strcmp(str, "warning") == 0) {
		return Log_Level::warning;
	}

	if (strcmp(str, "error") == 0) {
		return Log_Level::error;
	}

	return fallback;
}

const char* log_level_str(Log_Level level)
{
#ifdef __unix__
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
#else
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
#endif
}

void log_message(Log_Level level, const char* fmt, ...)
{
	if (log_level > (int)level)
		return;

	va_list args;
	va_start(args, fmt);
	fprintf(stdout, "[%s] ", log_level_str(level));

	char buffer[512];
	vsnprintf(buffer, 512, fmt, args);
	fputs(buffer, stdout);
	fputs("\n", stdout);

	va_end(args);

	for (Log_Observer* observer : observers) {
		observer->on_log(level, buffer);
	}
}
