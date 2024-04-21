#include "disable_player_actions.hpp"
#include "game_facade.hpp"

namespace Events
{

Disable_Player_Actions::Disable_Player_Actions(Game_Facade& facade) :
	Event{facade}
{
}

void Disable_Player_Actions::update(float)
{
	m_game_facade.set_player_interactions_enabled(false);
	m_activated = true;
}

bool Disable_Player_Actions::is_finished() const
{
	return m_activated;
}

void Disable_Player_Actions::reset()
{
	m_activated = false;
}

}
