#pragma once

#include "graphics/editor_ui/system.hpp"

namespace Editor
{

class Editor
{
public:
	Editor();
	void rebuild(); // Call when opened
	void draw(float dt);
	void input_char(char character);
	void input_key(int key);
private:
	Editor_UI::System m_gui;
	Editor_UI::Context m_context;
};

};
