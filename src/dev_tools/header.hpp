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
	Dev_Tools_Header(Game_Facade&, Game_Logic&, const String& project_root);

	void close_map_dialog();

	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> make_dialog_or_dummy();

	Game_Facade& m_game_facade; // FIXME - don't pass this
	Game_Logic& m_game_logic;
	String m_project_root;

	bool m_show_file_dialog = false;
	bool m_dirty = true;
};
