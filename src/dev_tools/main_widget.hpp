#pragma once

#include "graphics/editor_ui/state.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/string.hpp"

class Game_Facade;
class Game_Logic;
class Sequence_Manager;
class Item_Registry;

class Dev_Tools_Main_Widget final : public Editor_UI::State
{
public:
	Dev_Tools_Main_Widget(Game_Facade&, Game_Logic&, Sequence_Manager&, String project_root);
	Own_Ptr<Editor_UI::Widget_Factory> build(const Editor_UI::Theme& theme) override;
	bool is_dirty() const override;
private:
	Own_Ptr<Editor_UI::Widget_Factory> make_nav_rail_pane(const Editor_UI::Theme& theme);
	Own_Ptr<Editor_UI::Widget_Factory> make_right_pane();
	Own_Ptr<Editor_UI::Widget_Factory> make_header_pane();

	Game_Facade& m_game_facade;
	Game_Logic& m_game_logic;
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
