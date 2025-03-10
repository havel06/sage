#include "game_logic.hpp"
#include "game/game_logic_state_normal.hpp"
#include "game/game_logic_state_combat.hpp"
#include "combat/battle_desc.hpp"
#include "io/savegame/saveload_system.hpp"
#include "io/resource/sequence_manager.hpp"
#include "utils/log.hpp"

Game_Logic::Game_Logic(Saveload_System& saveload_system, Sequence_Manager& seq_mgr, Map_Manager& map_mgr, const String& start_sequence, Resource_Handle<Character_Profile> main_character) :
	party{main_character},
	state_normal{party, seq_mgr, saveload_system, map_mgr},
	state_combat{*this, seq_mgr, party},
	m_saveloader{saveload_system},
	m_sequence_manager{seq_mgr},
	m_start_sequence{start_sequence}
{
}

void Game_Logic::update(float time_delta)
{
	switch (m_state) {
		case Game_Logic_State::normal:
			state_normal.update({}, time_delta);
			break;
		case Game_Logic_State::combat:
			state_combat.update({}, time_delta);
			break;
		case Game_Logic_State::main_menu_to_normal:
		case Game_Logic_State::main_menu_to_combat:
			break; // Main menu is handled in input and rendering
		case Game_Logic_State::exit:
			break; // Do nothing
	}
}

void Game_Logic::exit_game()
{
	m_state = Game_Logic_State::exit;
}

void Game_Logic::continue_game()
{
	if (!m_saveloader.can_load())
		return;

	m_saveloader.load_game();

	if (m_state == Game_Logic_State::main_menu_to_normal)
		m_state = Game_Logic_State::normal;
	else if (m_state == Game_Logic_State::main_menu_to_combat)
		m_state = Game_Logic_State::combat;
}

void Game_Logic::new_game()
{
	m_saveloader.new_game();

	// Activate starting sequence
	m_sequence_manager.get(m_start_sequence, false).get().try_activate();
	SG_DEBUG("Activated start sequence.");

	m_state = Game_Logic_State::normal;
}

void Game_Logic::enter_combat(const Battle_Description& description)
{
	// Make sure that battle desc has got at least one enemy
	if (description.enemies.empty()) {
		SG_ERROR("Battle has no enemies.");
		return;
	}

	state_combat.start_battle({}, description);

	if (m_state == Game_Logic_State::main_menu_to_normal)
		m_state = Game_Logic_State::main_menu_to_combat;
	else
		m_state = Game_Logic_State::combat;
}

void Game_Logic::enter_normal_mode()
{
	m_state = Game_Logic_State::normal;
}
