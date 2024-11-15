#pragma once

#include "ui/widget.hpp"

class GUI_Loader;

class Scriptable_GUI
{
public:
	Scriptable_GUI(GUI_Loader& loader);
	void show_widget(const String& filename);
	void hide_widget();
	void draw(float time_delta);
private:
	GUI_Loader& m_loader;

	String m_filename;
	UI::Widget_Ptr m_widget;
};
