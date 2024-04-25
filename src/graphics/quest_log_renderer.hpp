#pragma once

class Quest_Log;

// FIXME - port to new UI system, after we have one

class Quest_Log_Renderer
{
public:
	Quest_Log_Renderer(const Quest_Log&);
	void draw();
private:

	const Quest_Log& m_quest_log;
};
