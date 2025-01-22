#pragma once
#include "game/game_facade.hpp"
#include "graphics/editor_ui/context.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/view_model.hpp"


// fwd
class Game_Logic_State_Normal;
namespace Editor_UI::Widgets {
	class Pane;
}

class Dev_Tools_Map_Dialog : public Editor_UI::View_Model
{
public:
	Dev_Tools_Map_Dialog(const Editor_UI::System& gui, Game_Logic_State_Normal& logic, const String& project_root);
	Dev_Tools_Map_Dialog(Dev_Tools_Map_Dialog&&) = delete;
	void toggle();

	Own_Ptr<Editor_UI::Widget> build() override;
	bool is_dirty() const override;
private:
	const Editor_UI::System& m_gui;
	Game_Logic_State_Normal& m_logic;

	String m_project_root;
	String m_requested_map;
	bool m_show = false;
	bool m_dirty = true;
};
