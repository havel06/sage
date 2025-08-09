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
#include "graphics/editor_ui/factories/spacer.hpp"

Dev_Tools_Mode_Items::Dev_Tools_Mode_Items(const Item_Registry& reg, Inventory& inv) :
	m_item_registry{reg},
	m_inventory{inv}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Mode_Items::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto column = Column::make(Column::Padding::small);

	m_item_registry.for_each([&](const Item& item){
		column
			->add(Row::make(true)
				->add(Row::make(false)
					->add(Editor_UI::Factories::Image::make(item.sprite, Vec2i{32, 32}))
					->add(Spacer::make(Vec2i{24, 0}))
					->add(Text::make(theme.font, item.id))
				)
				->add(Row::make(false)
					->add(Text::make(theme.font, String::from_int(m_inventory.get_item_count(item.id))))
					->add(Button::make(
						[this, id=item.id](){
							m_inventory.add_item(id, 1);
						})
						->with_icon(theme.ICON_ADD)
					)
				)
			)
			->add(Divider::make());
	});

	column->add(Button::make(
		[this](){
			m_inventory.clear();
		})
		->with_icon(theme.ICON_DELETE)
		->with_text(theme.font, "Clear")
	);

	return column;
}

bool Dev_Tools_Mode_Items::is_dirty() const
{
	return true; // FIXME - don't rebuild all the time?
}
