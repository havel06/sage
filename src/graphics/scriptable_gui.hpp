#pragma once

#include "ui/widget.hpp"

class Scriptable_GUI
{
public:
	void show_widget(UI::Widget_Ptr&& widget);
	void hide_widget();
	void draw(float time_delta);
private:
	UI::Widget_Ptr m_widget;
};
