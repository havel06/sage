#include "inventory_renderer.hpp"
#include "graphics/ui/image.hpp"
#include "graphics/ui/widget.hpp"
#include "graphics/ui/text.hpp"
#include "raylib/raylib.h"
#include "utils/string.hpp"
#include "utils/vec2.hpp"
#include "item/item.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "io/gui_loader.hpp"
#include "graphics/ui/box.hpp"

Inventory_Renderer::Inventory_Renderer(const Item_Registry& item_registry, const Inventory& inventory) :
	m_item_registry{item_registry},
	m_inventory{inventory}
{
}

void Inventory_Renderer::show(bool value)
{
	if (!m_main_widget)
		return;

	m_main_widget->show(value);
}

void Inventory_Renderer::draw(float dt)
{
	if (!m_main_widget || !m_slot_widget)
		return;

	// FIXME - safe cast
	UI::Box* slots_widget = (UI::Box*)m_main_widget->get_widget_by_name("Slots");

	slots_widget->clear_children();

	m_inventory.for_each_entry([&](const String& id, int count){
		if (count == 0)
			return;

		const Item& item = m_item_registry.get_item(id);

		UI::Widget_Ptr slot_widget = m_slot_widget->clone();

		// Image
		// FIXME - safe cast
		((UI::Image*)(m_slot_widget->get_widget_by_name("Image")))->sprite = item.sprite;

		// Count
		// FIXME - safe cast
		((UI::Text*)(m_slot_widget->get_widget_by_name("Count")))->text = String::from_int(count);

		slots_widget->add_child((UI::Widget_Ptr&&)slot_widget);
	});

	m_main_widget->draw_as_root(dt);
}

void Inventory_Renderer::load(GUI_Loader& loader, const String& project_root, const String& gui_filename, const String& gui_slot_filename)
{
	if (gui_filename.empty() || gui_slot_filename.empty())
		return;

	String slot_path = project_root;
	slot_path.append("/");
	slot_path.append(gui_slot_filename);

	String main_widget_path = project_root;
	main_widget_path.append("/");
	main_widget_path.append(gui_filename);

	m_slot_widget = loader.load(slot_path.data());
	m_main_widget = loader.load(main_widget_path.data());
}
