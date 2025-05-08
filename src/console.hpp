#pragma once

#include "utils/log.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"

class Console final : public Log_Observer
{
public:
	Console();
	Console(Console&&) = delete;

	void draw(float dt);
private:
	void on_log(Log_Level level, const char* message) override;

	struct Entry {
		Log_Level level;
		String message;
	};

	Array<Entry> m_entries;
};
