#pragma once

#include "graphics/editor_ui/context.hpp"
#include "header.hpp"
#include "mode_sequence.hpp"
#include "mode_entity.hpp"
#include "mode_items.hpp"
#include "graphics/editor_ui/system.hpp"
#include "utils/own_ptr.hpp"

// fwd
class User_Directory_Provider;

enum class Dev_Tools_Mode
{
	entities,
	sequence,
	items,
};

class Dev_Tools
{
public:
	// FIXME - use DI???
	Dev_Tools(Game_Facade& facade, Game_Logic& logic, Sequence_Manager& seq_mgr, const String& project_root);
	void update(Map& map); // Call when opened
	void draw(float dt);
	void input_char(char character);
	void input_key(int key);
private:
	Own_Ptr<Editor_UI::Widget> make_nav_rail_pane();
	Own_Ptr<Editor_UI::Widget> make_right_pane(Own_Ptr<Editor_UI::Widget>&& mode_items);
	Own_Ptr<Editor_UI::Widget> make_header_pane(Own_Ptr<Editor_UI::Widget>&& header);

	Editor_UI::System m_gui;

	Dev_Tools_Mode_Sequence m_sequence;
	Dev_Tools_Mode_Entity m_entity;

	Editor_UI::Context m_context;
	Editor_UI::Widgets::Stack* m_right_pane_stack = nullptr;

	Dev_Tools_Mode m_mode = Dev_Tools_Mode::items;
};
