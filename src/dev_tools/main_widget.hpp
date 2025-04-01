#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/string.hpp"

class Game_Facade;
class Game_Logic;
class Sequence_Manager;
class Item_Registry;

class Dev_Tools_Main_Widget final : public Editor_UI::State
{
public:
	Dev_Tools_Main_Widget(Editor_UI::System&, Game_Facade&, Game_Logic&, Sequence_Manager&, String project_root);
	Own_Ptr<Editor_UI::Widget_Factory2> build() override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory2> make_nav_rail_pane();
	Own_Ptr<Editor_UI::Widget_Factory2> make_right_pane();
	Own_Ptr<Editor_UI::Widget_Factory2> make_header_pane();

	Game_Facade& m_game_facade;
	Game_Logic& m_game_logic;
	Editor_UI::System& m_gui_system;
	Sequence_Manager& m_sequence_manager;
	String m_project_root;

	enum class Mode {
		entities = 0,
		sequence = 1,
		items = 2,
	};

	Mode m_mode = Mode::entities;
	bool m_dirty = true;
};
