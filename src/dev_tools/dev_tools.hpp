#pragma once

#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/system.hpp"
#include "utils/string.hpp"

class Game_Facade;
class Game_Logic;
class Sequence_Manager;

class Dev_Tools
{
public:
	Dev_Tools(Editor_UI::System& gui_system, Game_Facade& facade, Game_Logic& logic, Sequence_Manager& seq_mgr, const String& project_root);
	void rebuild(); // Call when opened
	void draw(float dt);
	void input_char(char character);
	void input_key(int key);
private:
	Editor_UI::Context m_context;

	Game_Facade& m_game_facade;
	Game_Logic& m_game_logic;
	Sequence_Manager& m_sequence_manager;
	String m_project_root;
};
