#include "select_target.hpp"
#include "combat/combat.hpp"
#include "game/game_facade.hpp"
#include "utils/log.hpp"

namespace Events
{

Select_Target::Select_Target(Game_Facade& facade, Target_Selection_Type selection_type) :
	Event{facade}
{
	m_selection_type = selection_type;
}

void Select_Target::update(float time_delta)
{
	(void)time_delta;

	// FIXME - different selection types
	
	if (!m_activated) {
		m_game_facade.combat_enter_target_selection();
		m_activated = true;
	}
}

bool Select_Target::is_finished() const
{
	return m_activated &&
		m_game_facade.get_combat_state() != Combat_State::hero_selecting_target &&
		m_game_facade.get_combat_state() != Combat_State::enemy_selecting_target;
}

void Select_Target::reset()
{
	m_activated = false;
}

}