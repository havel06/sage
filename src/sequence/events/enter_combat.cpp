#include "enter_combat.hpp"
#include "game_facade.hpp"

namespace Events
{

Enter_Combat::Enter_Combat(Game_Facade& facade) :
	Event{facade}
{
}

void Enter_Combat::update(float)
{
	m_game_facade.enter_combat();
	m_activated = true;
}

bool Enter_Combat::is_finished() const
{
	return m_activated;
}

void Enter_Combat::reset()
{
	m_activated = false;
}

}
