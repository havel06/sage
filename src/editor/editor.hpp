#pragma once

#include "graphics/editor_ui/system.hpp"

class GUI_Loader;

namespace Editor
{

class Editor
{
public:
	Editor(Editor_UI::System& gui_system, GUI_Loader&);
	void rebuild(); // Call when opened
	void draw(float dt);
	void input_char(char character);
	void input_key(int key);
private:
	GUI_Loader& m_gui_loader;

	Editor_UI::Context m_context;
};

};
