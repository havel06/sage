#include "enable_player_actions.hpp"
#include "game_facade.hpp"

namespace Events
{

Enable_Player_Actions::Enable_Player_Actions(Game_Facade& facade) :
	Event{facade}
{
}

void Enable_Player_Actions::update(float)
{
	m_game_facade.set_player_interactions_enabled(true);
	m_activated = true;
}

bool Enable_Player_Actions::is_finished() const
{
	return m_activated;
}

void Enable_Player_Actions::reset()
{
	m_activated = false;
}

}
