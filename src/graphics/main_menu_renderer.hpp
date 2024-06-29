#pragma once
#include "graphics/ui/layout.hpp"
#include "utils/string.hpp"

class GUI_Loader;

class Main_Menu_Renderer
{
public:
	void load(GUI_Loader&, const String& project_root);
	void input_direction(Direction);
	void enter();
	void draw(float time_delta);
private:
	UI::Widget_Ptr m_widget;
};
