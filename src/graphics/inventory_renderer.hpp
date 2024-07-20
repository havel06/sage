#pragma once

#include "graphics/ui/widget.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"
#include "item/inventory.hpp"

class Item_Registry;
class GUI_Loader;
struct Item;

class Inventory_Renderer : public Inventory_Observer
{
public:
	Inventory_Renderer(Item_Registry&, Inventory&);
	~Inventory_Renderer();
	void load(GUI_Loader&, const String& gui_filename, const String& gui_slot_filename);
	void show(bool value);
	void draw(float dt);

	void input_direction(Direction direction);
	void input_click();
private:
	void on_inventory_change() override; // Inventory_Observer

	Item_Registry& m_item_registry;
	Inventory& m_inventory;

	UI::Widget_Ptr m_slot_widget;
	UI::Widget_Ptr m_main_widget;
};
