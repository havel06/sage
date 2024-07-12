#include "change_target_hp.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Change_Target_HP::Change_Target_HP(Game_Facade& game_facade, int amount) :
	Event{game_facade}
{
	m_amount = amount;
}

void Change_Target_HP::update(float)
{
	m_game_facade.combat_change_target_hp(m_amount);
	m_activated = true;	
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
