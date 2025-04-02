#include "mode_items.hpp"
#include "graphics/editor_ui/factories/divider.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/system.hpp"
#include "item/item_registry.hpp"
#include "item/inventory.hpp"
#include "raylib/raylib.h"
#include "utils/own_ptr.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/image.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/text.hpp"

Dev_Tools_Mode_Items::Dev_Tools_Mode_Items(const Editor_UI::System& system, const Item_Registry& reg, Inventory& inv) :
	m_item_registry{reg},
	m_inventory{inv},
	m_gui_system{system}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Mode_Items::build()
{
	using namespace Editor_UI::Factories;

	auto column = Column::make(Column::Padding::small);

	m_item_registry.for_each([&](const Item& item){
		column
			->add(Row::make(true)
				->add(Row::make(false)
					->add(Editor_UI::Factories::Image::make(item.sprite, Vec2i{32, 32}))
					->add(Text::make(m_gui_system.get_font(), "      ")) // FIXME - spacer widget
					->add(Text::make(m_gui_system.get_font(), item.id))
				)
				->add(Row::make(false)
					->add(Text::make(m_gui_system.get_font(), String::from_int(m_inventory.get_item_count(item.id))))
					->add(Button::make(
						[this, id=item.id](){
							m_inventory.add_item(id, 1);
						})
						->with_icon(m_gui_system.ICON_ADD)
					)
				)
			)
			->add(Divider::make());
	});

	column->add(Button::make(
		[this](){
			m_inventory.clear();
		})
		->with_icon(m_gui_system.ICON_DELETE)
		->with_text(m_gui_system.get_font(), "Clear")
	);

	return column;
}

bool Dev_Tools_Mode_Items::is_dirty() const
{
	return true; // FIXME - don't rebuild all the time?
}
