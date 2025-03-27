#pragma once

#include "dev_tools/map_dialog.hpp"
#include "graphics/editor_ui/view_model.hpp"
#include "utils/string.hpp"
#include "graphics/editor_ui/context.hpp"

// fwd
class Map;
class Game_Facade;
class Game_Logic;
class Game_Logic_State_Normal;
namespace Editor_UI {
	class System;
	namespace Widgets {
		class Input;
		class Absolute_Pane;
	}
}

// FIXME - use new gui building api
class Dev_Tools_Header : public Editor_UI::View_Model
{
public:
	Dev_Tools_Header(const Font& font, Game_Facade&, Game_Logic&, const Editor_UI::System& gui, const String& project_root);

	void close_map_dialog();

	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	const Font& m_font;
	Game_Facade& m_game_facade; // FIXME - don't pass this
	Game_Logic& m_game_logic;
	const Editor_UI::System& m_gui_system;
	String m_project_root;

	bool m_show_file_dialog = false;
	bool m_dirty = true;
};
