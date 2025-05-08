#include "console.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>

Console::Console()
{
	log_add_observer(*this);
}

void Console::draw(float dt)
{
	(void)dt;
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{20, 20, 20, 220});
}

void Console::on_log(Log_Level level, const char* message)
{
	m_entries.push_back(Entry{level, message});

	if (m_entries.size() > 1024) {
		m_entries.remove(0);
	}
}
