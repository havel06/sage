#pragma once

#include "game_ui/widget.hpp"

class GUI_Loader;

class Scriptable_GUI
{
public:
	// Empty string = no widget shown
	const String& get_current_widget_filename() const { return m_filename; }

	Scriptable_GUI(GUI_Loader& loader);
	void show_widget(const String& filename);
	void hide_widget();
	void draw(float time_delta);
private:
	GUI_Loader& m_loader;

	String m_filename;
	Game_UI::Widget_Ptr m_widget;
};
