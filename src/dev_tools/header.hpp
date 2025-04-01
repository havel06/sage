#pragma once

#include "dev_tools/map_dialog.hpp"
#include "graphics/editor_ui/state.hpp"
#include "utils/string.hpp"
#include "graphics/editor_ui/context.hpp"

// fwd
class Map;
class Game_Facade;
class Game_Logic;
class Game_Logic_State_Normal;
namespace Editor_UI {
	class System;
}

class Dev_Tools_Header : public Editor_UI::State
{
public:
	Dev_Tools_Header(Game_Facade&, Game_Logic&, const Editor_UI::System& gui, const String& project_root);

	void close_map_dialog();

	Own_Ptr<Editor_UI::Widget_Factory2> build() override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory2> make_dialog_or_dummy();

	Game_Facade& m_game_facade; // FIXME - don't pass this
	Game_Logic& m_game_logic;
	const Editor_UI::System& m_gui_system;
	String m_project_root;

	bool m_show_file_dialog = false;
	bool m_dirty = true;
};
