#pragma once

#include "utils/string.hpp"
#include "party.hpp"
#include "game_logic_state_normal.hpp"
#include "game_logic_state_combat.hpp"

// fwd
class Game_Logic_State_Combat;
class Saveload_System;
class Sequence_Manager;
class Sequence_Saveloader;
struct Battle_Description;

enum class Game_Logic_State
{
	main_menu_to_normal,
	main_menu_to_combat,
	normal,
	combat,
	exit, // Game wants to be exited
};

class Game_Logic
{
public:
	Party party;
	Game_Logic_State_Normal state_normal;
	Game_Logic_State_Combat state_combat;

	Game_Logic(Saveload_System&, Sequence_Manager&, Map_Manager&, const String& start_sequence, Resource_Handle<Character_Profile> main_character);

	void update(float time_delta);
	Game_Logic_State get_state() const { return m_state; }
	void exit_game();

	// For main menu
	void continue_game();
	void new_game();

	// In and out of combat
	void enter_combat(const Battle_Description&);
	void enter_normal_mode();
private:
	Saveload_System& m_saveloader;
	Sequence_Manager& m_sequence_manager;

	Game_Logic_State m_state = Game_Logic_State::main_menu_to_normal;
	String m_start_sequence;
};
