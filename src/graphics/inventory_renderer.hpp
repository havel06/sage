#pragma once

#include "graphics/ui/widget.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"
#include "item/inventory.hpp"

class Item_Registry;
class GUI_Loader;
struct Item;

// TODO
//class Inventory_Renderer_Observer
//{
//public:
//	virtual void on_item_click();
//};


class Inventory_Renderer : public Inventory_Observer
{
public:
	Inventory_Renderer(const Item_Registry&, const Inventory&);
	~Inventory_Renderer();
	void load(GUI_Loader&, const String& gui_filename, const String& gui_slot_filename);
	void show(bool value);
	void draw(float dt);
	void input_direction(Direction direction);
private:
	void on_inventory_change() override; // Inventory_Observer

	const Item_Registry& m_item_registry;
	const Inventory& m_inventory;

	UI::Widget_Ptr m_slot_widget;
	UI::Widget_Ptr m_main_widget;
};
