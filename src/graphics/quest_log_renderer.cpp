#include "quest_log_renderer.hpp"
#include "quest/quest_log.hpp"
#include <raylib/raylib.h>

Quest_Log_Renderer::Quest_Log_Renderer(const Quest_Log& log) :
	m_quest_log{log}
{
}

void Quest_Log_Renderer::draw()
{
	if (m_quest_log.get_quest_count() == 0) {
		DrawText("No active quests", 100, 100, 40, WHITE);
		return;
	}

	int x = 200;
	int y = 200;

	for (int i = 0; i < m_quest_log.get_quest_count(); i++) {
		const Quest& quest = m_quest_log.get_quest(i);

		DrawRectangle(x, y, 500, 70, DARKGRAY);
		DrawText(quest.name.data(), x + 10, y, 30, WHITE);
		DrawText(quest.description.data(), x + 10, y + 40, 20, WHITE);
		y += 80;
	}
}
