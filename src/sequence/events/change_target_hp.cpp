#include "change_target_hp.hpp"
#include "utils/log.hpp"

namespace Events
{

Change_Target_HP::Change_Target_HP(Game_Facade& game_facade, int amount) :
	Event{game_facade}
{
	m_amount = amount;
}

void Change_Target_HP::update(float)
{
	m_activated = true;	
	// FIXME
}

bool Change_Target_HP::is_finished() const
{
	return m_activated;
}

void Change_Target_HP::reset()
{
	m_activated = false;
}

}
