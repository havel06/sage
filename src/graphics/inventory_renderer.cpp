#include "inventory_renderer.hpp"
#include "graphics/game_ui/image.hpp"
#include "graphics/game_ui/layout.hpp"
#include "graphics/game_ui/size.hpp"
#include "graphics/game_ui/widget.hpp"
#include "graphics/game_ui/text.hpp"
#include "graphics/game_ui/button.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "utils/string.hpp"
#include "utils/move.hpp"
#include "utils/vec2.hpp"
#include "item/item.hpp"
#include "item/inventory.hpp"
#include "item/item_registry.hpp"
#include "io/gui_loader.hpp"
#include "graphics/game_ui/box.hpp"
#include "sequence/sequence.hpp"
#include "game_ui/widget_visitor.hpp"

Inventory_Renderer::Inventory_Renderer(Item_Registry& item_registry, Inventory& inventory, Resource_Handle<Font> default_font) :
	m_item_registry{item_registry},
	m_inventory{inventory},
	m_default_font{default_font}
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

	Game_UI::Widget* slots_widget = m_main_widget->get_widget_by_name("Slots");

	if (!slots_widget)
		return;

	slots_widget->clear_children();

	m_inventory.for_each_entry([&](const String& id, int count){
		if (count == 0)
			return;

		Item& item = m_item_registry.get_item(id);
		Game_UI::Widget_Ptr slot_widget = m_slot_widget->clone();

		// Image
		Game_UI::Widget* image_widget = slot_widget->get_widget_by_name("Image");
		if (image_widget) {
			Game_UI::Image_Widget_Visitor image_visitor{[&](Game_UI::Image& image){
				image.sprite = item.sprite;
			}};
			image_widget->accept_visitor(image_visitor);
		}

		// Count
		Game_UI::Widget* count_widget = slot_widget->get_widget_by_name("Count");
		if (count_widget) {
			Game_UI::Text_Widget_Visitor count_visitor{[&](Game_UI::Text& text){
				text.text = String::from_int(count);
			}};
			count_widget->accept_visitor(count_visitor);
		}

		// Button
		Game_UI::Widget* button_widget = slot_widget->get_widget_by_name("Button");
		if (button_widget) {
			Game_UI::Button_Widget_Visitor button_visitor{[&](Game_UI::Button& button){
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
	if (gui_filename.empty() || gui_slot_filename.empty()) {
		use_fallback_widgets();
		return;
	}

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

bool Inventory_Renderer::is_inventory_empty() const
{
	return m_inventory.is_empty();
}

void Inventory_Renderer::use_fallback_widgets()
{
	Array<Game_UI::Size> auto_rows;
	auto_rows.push_back(Game_UI::Size{.automatic = true});
	Array<Game_UI::Size> auto_columns;
	auto_columns.push_back(Game_UI::Size{.automatic = true});

	// Main widget
	auto main_widget = make_own_ptr<Game_UI::Box>(Game_UI::Layout{auto_rows, auto_columns});

	// Slots widget
	Array<Game_UI::Size> slots_rows;
	slots_rows.push_back(Game_UI::Size{ .pixels = 100 });

	Array<Game_UI::Size> slots_columns;
	slots_columns.push_back(Game_UI::Size{ .pixels = 100 });
	slots_columns.push_back(Game_UI::Size{ .pixels = 100 });
	slots_columns.push_back(Game_UI::Size{ .pixels = 100 });
	slots_columns.push_back(Game_UI::Size{ .pixels = 100 });

	Game_UI::Layout slots_layout{slots_rows, slots_columns};
	auto slots_widget = make_own_ptr<Game_UI::Box>(move(slots_layout));
	slots_widget->set_name("Slots");

	// Slot widget
	auto slot_button_normal = make_own_ptr<Game_UI::Box>(Game_UI::Layout{auto_rows, auto_columns});
	auto slot_button_focused = make_own_ptr<Game_UI::Box>(Game_UI::Layout{auto_rows, auto_columns});
	slot_button_normal->colour = Colour{100, 100, 100, 255};
	slot_button_focused->colour = Colour{160, 160, 160, 255};
	auto slot_button = make_own_ptr<Game_UI::Button>(
		move(slot_button_normal), move(slot_button_focused), Game_UI::Layout{auto_rows, auto_columns}
	);
	slot_button->set_name("Button");

	// Slot image
	auto slot_image = make_own_ptr<Game_UI::Image>(Game_UI::Layout{auto_rows, auto_columns});
	slot_image->set_name("Image");

	// Slot count
	auto slot_count = make_own_ptr<Game_UI::Text>(m_default_font, Game_UI::Layout{auto_rows, auto_columns});
	slot_count->set_name("Count");

	// Put it all together
	slot_button->add_child(move(slot_image));
	slot_button->add_child(move(slot_count));
	m_slot_widget = move(slot_button);

	main_widget->add_child(move(slots_widget));
	m_main_widget = move(main_widget);
}
