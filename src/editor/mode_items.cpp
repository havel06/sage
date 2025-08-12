#include "mode_items.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/divider.hpp"
#include "graphics/editor_ui/factories/image.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/relative_pane.hpp"
#include "graphics/editor_ui/factories/spacer.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"
#include "item/item_registry.hpp"
#include "item_edit_dialog.hpp"


namespace Editor
{

Mode_Items::Mode_Items(Item_Registry& item_registry) :
	m_item_registry{item_registry}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Mode_Items::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	m_dirty = false;

	if (m_current_shown_item.has_value()) {
		return Stateful::make(make_own_ptr<Item_Edit_Dialog>(m_item_registry.get_item(m_current_shown_item.value())));
	}

	auto* column = Column::make(Column::Padding::small);

	m_item_registry.for_each([&](const Item& item){
		auto callback = [this, id=item.id](){
			m_current_shown_item = id;
			m_dirty = true;
		};

		column
			->add(Row::make(true)
				->add(Row::make(false)
					->add(Editor_UI::Factories::Image::make(item.sprite, Vec2i{32, 32}))
					->add(Spacer::make(Vec2i{24, 0}))
					->add(Text::make(theme.font, item.id))
					->add(Spacer::make(Vec2i{24, 0}))
					->add(Text::make(theme.font, item.name))
				)
				->add(Button::make(callback)
					->with_text(theme.font, "Edit")
				)
			)
			->add(Divider::make());
	});

	return Relative_Pane::make(true, column);
}

}
