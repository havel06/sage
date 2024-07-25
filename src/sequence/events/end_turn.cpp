#include "end_turn.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"

namespace Events
{

End_Turn::End_Turn(Game_Facade& game_facade) :
	Event{game_facade}
{
}

void End_Turn::update(float)
{
	m_game_facade.combat_end_turn();
	m_activated = true;	
}

bool End_Turn::is_finished() const
{
	return m_activated;
}

void End_Turn::reset()
{
	m_activated = false;
}

}
