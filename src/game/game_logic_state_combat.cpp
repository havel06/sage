#include "game_logic_state_combat.hpp"
#include "combat/combat.hpp"
#include "game_logic.hpp"
#include "combat/battle_desc.hpp"

Game_Logic_State_Combat::Game_Logic_State_Combat(Game_Logic& logic, Combat& combat) :
	m_logic{logic},
	m_combat{combat}
{
}

void Game_Logic_State_Combat::update(float time_delta)
{
	(void)time_delta;

	// Combat mode
	m_combat.update();
	Combat_Result result = m_combat.get_current_result();
	if (result == Combat_Result::won || result == Combat_Result::lost) {
		m_logic.enter_normal_mode();
	}
}

void Game_Logic_State_Combat::start_battle(const Battle_Description& description)
{
	m_combat.start_battle(description);
}
