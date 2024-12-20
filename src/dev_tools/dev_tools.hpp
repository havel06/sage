#pragma once

#include "mode_general.hpp"
#include "mode_sequence.hpp"
#include "mode_entity.hpp"
#include "mode_items.hpp"
#include "graphics/editor_ui/system.hpp"

// fwd
class User_Directory_Provider;

enum class Dev_Tools_Mode
{
	general,
	entities,
	sequence,
	items,
};

class Dev_Tools
{
public:
	// FIXME - use DI???
	Dev_Tools(User_Directory_Provider&, Game_Facade& facade, Game_Logic& logic, Sequence_Manager& seq_mgr, const Item_Registry&, Inventory&, const String& project_root);
	~Dev_Tools();
	void draw(Map& map, const String& map_filename);
private:
	void draw_main_menu();

	User_Directory_Provider& m_user_dir_provider;

	Editor_UI::System m_gui;
	Dev_Tools_Mode_General m_general;
	Dev_Tools_Mode_Sequence m_sequence;
	Dev_Tools_Mode_Entity m_entity;
	Dev_Tools_Mode_Items m_items;

	Dev_Tools_Mode m_mode = Dev_Tools_Mode::general;

};
