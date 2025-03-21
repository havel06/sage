#pragma once

#include "graphics/game_ui/widget.hpp"
#include "utils/vec2.hpp"
#include "utils/string.hpp"
#include "item/inventory.hpp"
#include "io/resource/resource_handle.hpp"
#include <raylib/raylib.h>

class Item_Registry;
class GUI_Loader;
struct Item;

class Inventory_Renderer_Observer
{
public:
	virtual void on_item_activate(Item&) = 0;
};

class Inventory_Renderer : public Inventory_Observer
{
public:
	Inventory_Renderer(Item_Registry&, Inventory&, Resource_Handle<Font> default_font);
	~Inventory_Renderer();

	void add_observer(Inventory_Renderer_Observer&);

	void load(GUI_Loader&, const String& gui_filename, const String& gui_slot_filename);
	void show(bool value);
	void draw(float dt);

	bool is_inventory_empty() const;

	void input_direction(Direction direction);
	void input_click();

	Item& get_current_selected_item();
private:
	void use_fallback_widgets();
	void on_inventory_change() override; // Inventory_Observer

	Item_Registry& m_item_registry;
	Inventory& m_inventory;

	Array<Inventory_Renderer_Observer*> m_observers;
	Resource_Handle<Font> m_default_font;
	Game_UI::Widget_Ptr m_slot_widget;
	Game_UI::Widget_Ptr m_main_widget;
};
