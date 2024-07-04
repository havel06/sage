#include "scriptable_gui.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"

void Scriptable_GUI::show_widget(UI::Widget_Ptr&& widget)
{
	m_widget = move(widget);
	m_widget->show(true);
}

void Scriptable_GUI::hide_widget()
{
	if (m_widget)
		m_widget->show(false);
}

void Scriptable_GUI::draw(float time_delta)
{
	if (m_widget) {
		m_widget->draw_as_root(time_delta);
	}
}
