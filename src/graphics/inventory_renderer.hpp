#pragma once

#include "utils/vec2.hpp"

class Inventory;
class Item_Registry;
struct Item;


// FIXME - port to new UI system, after we have one

class Inventory_Renderer
{
public:
	Inventory_Renderer(const Item_Registry&, const Inventory&);
	void draw();
private:
	void draw_slot_background(int index_x, int index_y);
	void draw_slot_item(int index, const Item& item, int count);
	Vec2i calculate_slot_position(int index_x, int index_y);

	const int m_slot_size = 74;
	const int m_slot_item_size = 64;
	const int m_slot_margin = 6;
	const int m_slots_horizontal = 10;
	const int m_slots_vertical = 6;

	const Item_Registry& m_item_registry;
	const Inventory& m_inventory;
};
