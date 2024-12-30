#pragma once
#include "game/game_facade.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/system.hpp"


// fwd
class Game_Logic_State_Normal;
namespace Editor_UI::Widgets {
	class Pane;
}

class Dev_Tools_Map_Dialog
{
public:
	// FIXME - don't pass Game_Facade
	Dev_Tools_Map_Dialog(const Editor_UI::System& gui, Game_Logic_State_Normal& logic, Game_Facade& facade, const String& project_root);
	void draw(float dt);
	void reset_map_input();
	void input_char(char character);
	void input_key(int key);
private:
	const Editor_UI::System& m_gui;
	Game_Logic_State_Normal& m_logic;
	Game_Facade& m_facade;

	String m_project_root;
	Editor_UI::Context m_context;
	Editor_UI::Widgets::Pane* m_pane = nullptr;
	Editor_UI::Widgets::Input* m_input = nullptr;
};
