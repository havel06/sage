#include "change_all_enemy_units_hp.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Change_All_Enemy_Units_HP::Change_All_Enemy_Units_HP(Game_Facade& game_facade, int amount) :
	Event{game_facade}
{
	m_amount = amount;
}

void Change_All_Enemy_Units_HP::update(float)
{
	SG_DEBUG("Change all enemy units hp by %d", m_amount);
	m_game_facade.combat_change_all_enemy_units_hp(m_amount);
	m_activated = true;	
}

bool Change_All_Enemy_Units_HP::is_finished() const
{
	return m_activated;
}

void Change_All_Enemy_Units_HP::reset()
{
	m_activated = false;
}

}
