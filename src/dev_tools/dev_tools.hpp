#pragma once

#include "graphics/editor_ui/context.hpp"
#include "header.hpp"
#include "mode_sequence.hpp"
#include "mode_entity.hpp"
#include "mode_items.hpp"
#include "graphics/editor_ui/system.hpp"

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
	Dev_Tools(User_Directory_Provider&, Game_Facade& facade, Game_Logic& logic, Game_Logic_State_Normal&, Sequence_Manager& seq_mgr, const Item_Registry&, Inventory&, const String& project_root);
	~Dev_Tools();
	void update(Map& map); // Call when opened
	void draw(float dt);
	void input_char(char character);
	void input_key(int key);
private:
	User_Directory_Provider& m_user_dir_provider;

	Editor_UI::System m_gui;

	Dev_Tools_Header m_header;
	Dev_Tools_Mode_Sequence m_sequence;
	Dev_Tools_Mode_Entity m_entity;
	Dev_Tools_Mode_Items m_items;

	Editor_UI::Context m_context;
	Editor_UI::Widgets::Pane* m_header_pane = nullptr;
	Editor_UI::Widgets::Pane* m_right_pane = nullptr;
	Editor_UI::Widgets::Stack* m_right_pane_stack = nullptr;

	Dev_Tools_Mode m_mode = Dev_Tools_Mode::items;
};
