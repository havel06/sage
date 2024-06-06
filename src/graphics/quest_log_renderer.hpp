#pragma once
#include "utils/string.hpp"
#include "ui/widget.hpp"

// fwd
class Quest_Log;
class GUI_Loader;

class Quest_Log_Renderer
{
public:
	Quest_Log_Renderer(const Quest_Log&);
	void load(GUI_Loader&, const String& project_root);
	void draw();
private:
	const Quest_Log& m_quest_log;

	UI::Widget_Ptr m_log_widget;
	UI::Widget_Ptr m_quest_widget;
};
