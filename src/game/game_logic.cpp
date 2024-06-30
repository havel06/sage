#include "game_logic.hpp"
#include "game/game_logic_state_normal.hpp"
#include "game/game_logic_state_combat.hpp"
#include "combat/battle_desc.hpp"

Game_Logic::Game_Logic(Game_Logic_State_Normal& normal, Game_Logic_State_Combat& combat) :
	m_state_normal{normal},
	m_state_combat{combat}
{
}

void Game_Logic::update(float time_delta)
{
	switch (m_state) {
		case Game_Logic_State::normal:
			m_state_normal.update(time_delta);
		case Game_Logic_State::combat:
			m_state_normal.update(time_delta);
	}
}


void Game_Logic::enter_combat(const Battle_Description& description)
{
	m_state_combat.start_battle(description);
	m_state = Game_Logic_State::combat;
}

void Game_Logic::enter_normal_mode()
{
	m_state = Game_Logic_State::normal;
}
