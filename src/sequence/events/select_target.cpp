#include "select_target.hpp"
#include "combat/battle_turn.hpp"
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

	if (!m_activated) {
		m_game_facade.combat_enter_target_selection(m_selection_type);
		m_activated = true;
	}
}

bool Select_Target::is_finished() const
{
	return m_activated &&
		m_game_facade.combat_get_battle_turn_state() != Battle_Turn_State::selecting_ally_target &&
		m_game_facade.combat_get_battle_turn_state() != Battle_Turn_State::selecting_enemy_target;
}

void Select_Target::reset()
{
	m_activated = false;
}

}
