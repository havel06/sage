#pragma once

enum class Log_Level
{
	debug   = 0,
	info    = 1,
	warning = 2,
	error   = 3
};

void log_message(Log_Level level, const char* fmt, ...);
void set_log_level(Log_Level);
Log_Level log_level_from_string(const char*, Log_Level fallback);

#define SG_DEBUG(...) log_message(Log_Level::debug, __VA_ARGS__)
#define SG_INFO(...) log_message(Log_Level::info, __VA_ARGS__)
#define SG_WARNING(...) log_message(Log_Level::warning, __VA_ARGS__)
#define SG_ERROR(...) log_message(Log_Level::error, __VA_ARGS__)
