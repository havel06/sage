#pragma once

#include "utils/string.hpp"
#include "graphics/editor_ui/context.hpp"

// fwd
class Map;
class Game_Facade;
class Game_Logic;
namespace Editor_UI {
	class System;
	namespace Widgets {
		class Input;
		class Pane;
	}
}

class Dev_Tools_Header
{
public:
	Dev_Tools_Header(Game_Facade&, Game_Logic&, const Editor_UI::System& gui, const String& project_root);
	void draw(const String& map_filename, float dt);
	void input_char(char character);
	void input_key(int key);
private:
	Game_Facade& m_game_facade;
	Game_Logic& m_game_logic;
	const Editor_UI::System& m_gui_system;

	String m_project_root;
	Editor_UI::Context m_context;
	Editor_UI::Widgets::Pane* m_pane = nullptr;
	Editor_UI::Widgets::Input* m_map_input = nullptr;
};
