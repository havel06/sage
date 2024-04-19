#include "inventory_renderer.hpp"
#include "raylib/raylib.h"
#include "utils/string.hpp"
#include "utils/vec2.hpp"
#include "item/item.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"

Inventory_Renderer::Inventory_Renderer(const Item_Registry& item_registry, const Inventory& inventory) :
	m_item_registry{item_registry},
	m_inventory{inventory}
{
}

void Inventory_Renderer::draw()
{
	// Background
	for (int y = 0; y < m_slots_vertical; y++)
	{
		for (int x = 0; x < m_slots_horizontal; x++) {
			draw_slot_background(x, y);
		}
	}

	// Foreground
	int index = 0;
	m_inventory.for_each_entry([&](const String& id, int count){
		if (count == 0)
			return;

		const Item& item = m_item_registry.get_item(id);
		draw_slot_item(index, item, count);
		index++;
	});
}

void Inventory_Renderer::draw_slot_background(int index_x, int index_y)
{
	Vec2i position = calculate_slot_position(index_x, index_y);

	// Background
	const Color background_colour = Color{0, 0, 0, 222};
	DrawRectangle(position.x, position.y, m_slot_size, m_slot_size, background_colour);
	// Outline
	DrawRectangleLinesEx(
		Rectangle {(float)position.x, (float)position.y, (float)m_slot_size, (float)m_slot_size},
		2,
		GRAY);
}

void Inventory_Renderer::draw_slot_item(int index, const Item& item, int count)
{
	const int index_x = index % m_slots_horizontal;
	const int index_y = index / m_slots_vertical;

	Vec2i slot_position = calculate_slot_position(index_x, index_y);
	const int padding = (m_slot_size - m_slot_item_size) / 2;
	Vec2i item_position = slot_position + Vec2i{padding, padding};

	item.sprite.draw(Rectf{
		.position = item_position,
		.size = Vec2i{m_slot_item_size, m_slot_item_size}
	});

	String count_str = String::from_int(count);
	DrawText(count_str.data(), slot_position.x + 4, slot_position.y + 4, 16, WHITE);
}

Vec2i Inventory_Renderer::calculate_slot_position(int index_x, int index_y)
{
	const int total_width =
		m_slots_horizontal * m_slot_size + (m_slots_horizontal - 1) * m_slot_margin;
	const int total_height = 
		m_slots_vertical * m_slot_size + (m_slots_vertical - 1) * m_slot_margin;

	const int first_slot_x = (GetScreenWidth() - total_width) / 2;
	const int first_slot_y = (GetScreenHeight() - total_height) / 2;

	const int slot_x = first_slot_x + index_x * (m_slot_size + m_slot_margin);
	const int slot_y = first_slot_y + index_y * (m_slot_size + m_slot_margin);

	return {slot_x, slot_y};
}
