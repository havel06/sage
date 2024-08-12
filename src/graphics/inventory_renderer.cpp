#include "inventory_renderer.hpp"
#include "graphics/ui/image.hpp"
#include "graphics/ui/widget.hpp"
#include "graphics/ui/text.hpp"
#include "graphics/ui/button.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "utils/string.hpp"
#include "utils/move.hpp"
#include "utils/vec2.hpp"
#include "item/item.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "io/gui_loader.hpp"
#include "graphics/ui/box.hpp"
#include "sequence/sequence.hpp"
#include "ui/widget_visitor.hpp"

Inventory_Renderer::Inventory_Renderer(Item_Registry& item_registry, Inventory& inventory) :
	m_item_registry{item_registry},
	m_inventory{inventory}
{
	m_inventory.add_observer(*this);
}

Inventory_Renderer::~Inventory_Renderer()
{
	m_inventory.remove_observer(*this);
}

void Inventory_Renderer::show(bool value)
{
	if (!m_main_widget)
		return;

	m_main_widget->show(value);
}

void Inventory_Renderer::add_observer(Inventory_Renderer_Observer& observer)
{
	m_observers.push_back(&observer);
}

void Inventory_Renderer::on_inventory_change()
{
	SG_DEBUG("update inventory content");

	if (!m_main_widget || !m_slot_widget)
		return;

	UI::Widget* slots_widget = m_main_widget->get_widget_by_name("Slots");

	if (!slots_widget)
		return;

	slots_widget->clear_children();

	m_inventory.for_each_entry([&](const String& id, int count){
		if (count == 0)
			return;

		Item& item = m_item_registry.get_item(id);
		UI::Widget_Ptr slot_widget = m_slot_widget->clone();

		// Image
		UI::Widget* image_widget = slot_widget->get_widget_by_name("Image");
		if (image_widget) {
			UI::Image_Widget_Visitor image_visitor{[&](UI::Image& image){
				image.sprite = item.sprite;
			}};
			image_widget->accept_visitor(image_visitor);
		}

		// Count
		UI::Widget* count_widget = slot_widget->get_widget_by_name("Count");
		if (count_widget) {
			UI::Text_Widget_Visitor count_visitor{[&](UI::Text& text){
				text.text = String::from_int(count);
			}};
			count_widget->accept_visitor(count_visitor);
		}

		// Button
		UI::Widget* button_widget = slot_widget->get_widget_by_name("Button");
		if (button_widget) {
			UI::Button_Widget_Visitor button_visitor{[&](UI::Button& button){
				button.on_click = [&](){
					if (item.assigned_sequence.has_value()) {
						item.assigned_sequence.value().get().try_activate();
					}

					// Notify observers
					for (auto* observer : m_observers) {
						observer->on_item_activate(item);
					}
				};
			}};
			button_widget->accept_visitor(button_visitor);
		}

		slots_widget->add_child(move(slot_widget));
	});

	m_main_widget->focus_first();
}

void Inventory_Renderer::draw(float dt)
{
	if (!m_main_widget || !m_slot_widget)
		return;

	m_main_widget->draw_as_root(dt);
}

void Inventory_Renderer::load(GUI_Loader& loader, const String& gui_filename, const String& gui_slot_filename)
{
	if (gui_filename.empty() || gui_slot_filename.empty())
		return;

	m_slot_widget = loader.load(gui_slot_filename);
	m_main_widget = loader.load(gui_filename);
}

void Inventory_Renderer::input_direction(Direction direction)
{
	m_main_widget->move_focus(direction);
}

void Inventory_Renderer::input_click()
{
	m_main_widget->process_click();
}
