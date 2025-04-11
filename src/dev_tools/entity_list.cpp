#include "entity_list.hpp"
#include "map/entity.hpp"
#include "map/map.hpp"
#include "entity_detail.hpp"
#include "utils/function_wrapper.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/divider.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/scroll.hpp"
#include "utils/log.hpp"
#include "utils/fuzzy_match.hpp"

Dev_Tools_Entity_List::Dev_Tools_Entity_List(Map_Entities& entities, Dev_Tools_Entity_Detail& detail, const String& searched_term) :
	m_detail{detail},
	m_entities{entities},
	m_searched_term{searched_term}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Entity_List::build(const Editor_UI::Theme& theme)
{
	m_dirty = false;
	
	using namespace Editor_UI::Factories;

	auto column = Column::make(Column::Padding::small);

	for (int i = 0; i < m_entities.get_entity_count(); i++) {
		Entity& entity = m_entities.get_entity(i);

		if (fuzzy_match_string(m_searched_term, entity.name)) {
			column
				->add(build_item(entity, theme))
				->add(Divider::make());
		}
	}

	return Scroll::make(m_scroll_state, move(column));
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Entity_List::build_item(Entity& entity, const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto button_callback = [this, &entity](){
		m_detail.set_entity(&entity);
	};

	return Row::make(true)
		->add(Text::make(theme.font, entity.name))
		->add(Button::make(button_callback)
			->with_icon(theme.ICON_INFO));
}

bool Dev_Tools_Entity_List::is_dirty() const
{
	return m_dirty;
}
