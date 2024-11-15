#include "scriptable_gui.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"
#include "io/gui_loader.hpp"

Scriptable_GUI::Scriptable_GUI(GUI_Loader& loader) :
	m_loader{loader}
{
}

void Scriptable_GUI::show_widget(const String& filename)
{
	m_widget = m_loader.load(filename);
	m_filename = filename;
	m_widget->show(true);
}

void Scriptable_GUI::hide_widget()
{
	if (m_widget)
		m_widget->show(false);

	m_filename = "";
}

void Scriptable_GUI::draw(float time_delta)
{
	if (m_widget) {
		m_widget->draw_as_root(time_delta);
	}
}
