#pragma once
#include "game/game_facade.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/state.hpp"


// fwd
class Game_Logic_State_Normal;
class Dev_Tools_Header;
namespace Editor_UI::Widgets {
	class Absolute_Pane;
}

class Dev_Tools_Map_Dialog : public Editor_UI::State
{
public:
	Dev_Tools_Map_Dialog(Dev_Tools_Header&, const Font& font, const Editor_UI::System& gui, Game_Logic_State_Normal& logic, const String& project_root);
	Dev_Tools_Map_Dialog(Dev_Tools_Map_Dialog&&) = delete;

	Own_Ptr<Editor_UI::Widget_Factory> build() override;
	bool is_dirty() const override;
private:
	Array<String> get_input_hints();

	Dev_Tools_Header& m_header;
	const Editor_UI::System& m_gui;
	Game_Logic_State_Normal& m_logic;
	const Font& m_font;

	String m_project_root;
	String m_requested_map;
	bool m_dirty = true;
};
