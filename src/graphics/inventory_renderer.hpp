#pragma once

#include "utils/vec2.hpp"

class Inventory;

class Inventory_Renderer
{
public:
	Inventory_Renderer(const Inventory&);
	void draw();
private:
	void draw_slot_background(int index_x, int index_y);
	Vec2i calculate_slot_position(int index_x, int index_y);

	const int m_slot_size = 72;
	const int m_slot_item_size = 64;
	const int m_slot_margin = 6;
	const int m_slots_horizontal = 10;
	const int m_slots_vertical = 6;

	const Inventory& m_inventory;
};
