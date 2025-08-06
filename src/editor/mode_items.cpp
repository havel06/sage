#include "mode_items.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/divider.hpp"
#include "graphics/editor_ui/factories/image.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "item/item_registry.hpp"


namespace Editor
{

Mode_Items::Mode_Items(Item_Registry& item_registry) :
	m_item_registry{item_registry}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Mode_Items::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto* column = Column::make(Column::Padding::small);

	// FIXME - show assigned sequence

	m_item_registry.for_each([&](const Item& item){
		column
			->add(Row::make(true)
				->add(Row::make(false)
					->add(Editor_UI::Factories::Image::make(item.sprite, Vec2i{32, 32}))
					->add(Text::make(theme.font, "      ")) // FIXME - spacer widget
					->add(Text::make(theme.font, item.id))
					->add(Text::make(theme.font, "      ")) // FIXME - spacer widget
					->add(Text::make(theme.font, item.name))
				)
			)
			->add(Divider::make());
	});

	return column;
}

}
