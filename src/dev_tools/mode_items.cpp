#include "mode_items.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/image.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/system.hpp"
#include "item/item_registry.hpp"
#include "item/inventory.hpp"
#include "imgui.h"
#include "raylib/raylib.h"
#include "utils/own_ptr.hpp"

Dev_Tools_Mode_Items::Dev_Tools_Mode_Items(const Editor_UI::System& system, const Item_Registry& reg, Inventory& inv) :
	m_item_registry{reg},
	m_inventory{inv},
	m_gui_system{system}
{
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Mode_Items::build()
{
	Editor_UI::Widget_Factory factory = m_gui_system.get_widget_factory();

	auto column = factory.make_column();
	column->padding = Editor_UI::Theme::PADDING_SMALL;

	m_item_registry.for_each([&](const Item& item){
		// Left side
		auto row_left = factory.make_row();
		row_left->add_child(factory.make_image(item.sprite, Vec2i{32, 32}));
		// FIXME - replace with some sort of a spacer widget
		row_left->add_child(factory.make_text("      "));
		row_left->add_child(factory.make_text(item.id));

		// Right side
		auto row_right = factory.make_row();
		auto count = factory.make_text(String::from_int(m_inventory.get_item_count(item.id)));
		auto button = factory.make_icon_button(
			m_gui_system.ICON_ADD,
			[this, id=item.id](){
				m_inventory.add_item(id, 1);
			}
		);
		row_right->add_child(move(count));
		row_right->add_child(move(button));

		auto row_main = factory.make_row(true);
		row_main->add_child(move(row_left));
		row_main->add_child(move(row_right));
		column->add_child(move(row_main));
		column->add_child(factory.make_divider());
	});

	auto delete_button = factory.make_button(
		"Clear",
		&m_gui_system.ICON_DELETE,
		[this](){
			m_inventory.clear();
		}
	);

	column->add_child(move(delete_button));

	return column;
}

bool Dev_Tools_Mode_Items::is_dirty() const
{
	return true; // FIXME - don't rebuild all the time?
}
