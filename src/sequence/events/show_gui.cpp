#include "show_gui.hpp"
#include "utils/move.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Show_GUI::Show_GUI(Game_Facade& facade, UI::Widget_Ptr&& widget) :
	Event{facade}
{
	m_widget = move(widget);
}

void Show_GUI::update(float)
{
	m_game_facade.show_gui(m_widget->clone());
	m_activated = true;
}

bool Show_GUI::is_finished() const
{
	return m_activated;
}

void Show_GUI::reset()
{
	m_activated = false;
}

}
