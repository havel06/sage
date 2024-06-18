#include "inventory_renderer.hpp"
#include "graphics/ui/image.hpp"
#include "raylib/raylib.h"
#include "utils/string.hpp"
#include "utils/vec2.hpp"
#include "item/item.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "io/gui_loader.hpp"

Inventory_Renderer::Inventory_Renderer(const Item_Registry& item_registry, const Inventory& inventory) :
	m_item_registry{item_registry},
	m_inventory{inventory}
{
}

void Inventory_Renderer::draw()
{
	// Foreground
	int index = 0;
	m_inventory.for_each_entry([&](const String& id, int count){
		if (count == 0)
			return;

		const Item& item = m_item_registry.get_item(id);
		draw_slot(index, item, count);
		index++;
	});
}

void Inventory_Renderer::load(GUI_Loader& loader, const String& project_root)
{
	String path = project_root;
	path.append("/inventory_slot.json");
	m_slot_widget = loader.load(path.data());
}

void Inventory_Renderer::draw_slot(int index, const Item& item, int count)
{
	const int index_x = index % m_slots_horizontal;
	const int index_y = index / m_slots_vertical;

	const Vec2i position = calculate_slot_position(index_x, index_y);
	const Vec2i size = {74, 74};

	// FIXME - safe cast
	((UI::Image*)(m_slot_widget->get_widget_by_name("Image")))->sprite = item.sprite;

	// FIXME - time delta
	m_slot_widget->draw(Recti{position, size}, 0);

	// TODO
	(void)count;
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
