#include "game_logic_state_combat.hpp"
#include "combat/combat.hpp"
#include "game_logic.hpp"
#include "combat/battle_desc.hpp"
#include "io/resource/sequence_manager.hpp"

Game_Logic_State_Combat::Game_Logic_State_Combat(Game_Logic& logic, Combat& combat, Sequence_Manager& seq_mgr) :
	m_logic{logic},
	m_combat{combat},
	m_sequence_manager{seq_mgr}
{
}

void Game_Logic_State_Combat::update(float time_delta)
{
	// Update sequences
	m_sequence_manager.update(time_delta);
	m_combat.update();

	if (!m_combat.is_active()) {
		m_logic.enter_normal_mode();
	}
}

void Game_Logic_State_Combat::start_battle(const Battle_Description& description)
{
	m_combat.start_battle(description);
}
