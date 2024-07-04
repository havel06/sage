#include "hide_gui.hpp"
#include "utils/move.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Hide_GUI::Hide_GUI(Game_Facade& facade) :
	Event{facade}
{
}

void Hide_GUI::update(float)
{
	m_game_facade.hide_gui();
	m_activated = true;
}

bool Hide_GUI::is_finished() const
{
	return m_activated;
}

void Hide_GUI::reset()
{
	m_activated = false;
}

}
