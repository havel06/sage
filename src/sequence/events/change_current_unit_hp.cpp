#include "change_current_unit_hp.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Change_Current_Unit_HP::Change_Current_Unit_HP(Game_Facade& game_facade, int amount) :
	Event{game_facade}
{
	m_amount = amount;
}

void Change_Current_Unit_HP::update(float)
{
	m_game_facade.combat_change_current_unit_hp(m_amount);
	m_activated = true;	
}

bool Change_Current_Unit_HP::is_finished() const
{
	return m_activated;
}

void Change_Current_Unit_HP::reset()
{
	m_activated = false;
}

}
