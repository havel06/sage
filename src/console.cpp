#include "console.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>
#include <string.h>

static const int font_size = 20;

Console::Console()
{
	log_add_observer(*this);
}

Console::~Console()
{
	log_remove_observer(*this);
}

void Console::draw(float dt)
{
	(void)dt;

	// bg
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{20, 20, 20, 220});

	const int lines_fitted_on_screen = GetScreenHeight() / font_size;

	int first_entry_drawn = 0;

	if (m_entries.size() > lines_fitted_on_screen) {
		first_entry_drawn = m_entries.size() - lines_fitted_on_screen;
	}

	for (int i = first_entry_drawn; i < m_entries.size(); i++) {
		draw_entry(m_entries[i], i - first_entry_drawn);
	}
}

void Console::draw_entry(const Entry& entry, int index)
{
	// FIXME - refactor using Formatted_Text

	const int margin_x = 10;
	const int y = index * font_size;
	const int level_message_gap = 10;

	// Level
	const char* level_str = log_level_to_string(entry.level);
	int x = margin_x;
	DrawText("[", x, y, font_size, WHITE);
	x += MeasureText("[", font_size);
	DrawText(level_str, x, y, font_size, get_log_level_color(entry.level));
	x += MeasureText(level_str, font_size);
	DrawText("]", x, y, font_size, WHITE);
	x += MeasureText("]", font_size) + level_message_gap;

	// Text
	DrawText(entry.message.data(), x, y, font_size, WHITE);
}

const char* Console::log_level_to_string(Log_Level log_level)
{
	switch (log_level) {
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

Color Console::get_log_level_color(Log_Level level)
{
	switch (level) {
		case Log_Level::debug:
			return SKYBLUE;
		case Log_Level::error:
			return RED;
		case Log_Level::info:
			return LIME;
		case Log_Level::warning:
			return YELLOW;
	}
}

void Console::on_log(Log_Level level, const char* message)
{
	m_entries.push_back(Entry{level, message});

	if (m_entries.size() > 1024) {
		m_entries.remove(0);
	}
}
