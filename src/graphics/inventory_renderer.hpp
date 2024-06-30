#pragma once

#include "graphics/ui/widget.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"

class Inventory;
class Item_Registry;
class GUI_Loader;
struct Item;


// FIXME - port to new UI system, after we have one

class Inventory_Renderer
{
public:
	Inventory_Renderer(const Item_Registry&, const Inventory&);
	void load(GUI_Loader&, const String& project_root, const String& gui_filename, const String& gui_slot_filename);
	void draw();
private:
	const Item_Registry& m_item_registry;
	const Inventory& m_inventory;

	UI::Widget_Ptr m_slot_widget;
	UI::Widget_Ptr m_main_widget;
};
