#pragma once

#include "utils/string.hpp"

// fwd
class Game_Logic_State_Normal;
class Game_Logic_State_Combat;
class Game_Saveloader;
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
	Game_Logic(Game_Saveloader&, Sequence_Saveloader&, Sequence_Manager&, Game_Logic_State_Normal&, Game_Logic_State_Combat&, const String& start_sequence);

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
	Game_Logic_State m_state = Game_Logic_State::main_menu_to_normal;

	Game_Saveloader& m_saveloader;
	Sequence_Manager& m_sequence_manager;
	Sequence_Saveloader& m_sequence_saveloader;
	Game_Logic_State_Normal& m_state_normal;
	Game_Logic_State_Combat& m_state_combat;
	String m_start_sequence;
};
