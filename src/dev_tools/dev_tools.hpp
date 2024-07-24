#pragma once

#include "mode_general.hpp"
#include "mode_sequence.hpp"
#include "mode_entity.hpp"
#include "mode_items.hpp"

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
	// FIXME - use DI
	Dev_Tools(Game_Facade& facade, Sequence_Manager& seq_mgr, const Item_Registry&, Inventory&, const String& project_root);
	~Dev_Tools();
	void draw(Map&);
private:
	void draw_main_menu();

	Dev_Tools_Mode_General m_general;
	Dev_Tools_Mode_Sequence m_sequence;
	Dev_Tools_Mode_Entity m_entity;
	Dev_Tools_Mode_Items m_items;

	Dev_Tools_Mode m_mode = Dev_Tools_Mode::general;
};
