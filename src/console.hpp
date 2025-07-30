#pragma once

#include "utils/log.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"

class Console final : public Log_Observer
{
public:
	Console();
	Console(Console&&) = delete;
	~Console();

	void draw(float dt);
private:
	void on_log(Log_Level level, const char* message) override;

	struct Entry {
		Log_Level level;
		String message;
	};

	void draw_entry(const Entry& entry, int index);
	const char* log_level_to_string(Log_Level);
	struct Color get_log_level_color(Log_Level);

	Array<Entry> m_entries;
};
