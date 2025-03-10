#include "entity_list.hpp"
#include "map/entity.hpp"
#include "map/map.hpp"
#include "entity_detail.hpp"
#include "utils/function_wrapper.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/scroll.hpp"
#include "graphics/editor_ui/widgets/dummy.hpp"
#include "utils/log.hpp"
#include "utils/fuzzy_match.hpp"

Dev_Tools_Entity_List::Dev_Tools_Entity_List(Dev_Tools_Entity_Detail& detail, Editor_UI::System& system) :
	m_detail{detail},
	m_system{system}
{
}

void Dev_Tools_Entity_List::rebuild(Map_Entities& entities, const String& searched_term)
{
	m_entities = &entities;
	m_dirty = true;
	m_searched_term = searched_term;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Entity_List::build()
{
	Editor_UI::Widget_Factory factory = m_system.get_widget_factory();

	if (!m_entities)
		return factory.make_dummy();

	Own_Ptr<Editor_UI::Widgets::Column> column = factory.make_column();
	column->padding = Editor_UI::Widgets::Column_Padding::small;

	for (int i = 0; i < m_entities->get_entity_count(); i++) {
		Entity& entity = m_entities->get_entity(i);

		if (!fuzzy_match_string(m_searched_term, entity.name))
			continue;

		auto row = factory.make_row(true);
		row->add_child(factory.make_text(entity.name));
		row->add_child(
			factory.make_icon_button(
				m_system.ICON_INFO,
				[i, this](){
					m_detail.set_entity(&m_entities->get_entity(i));
				}
			)
		);
		column->add_child(move(row));
		column->add_child(factory.make_divider());
	}

	m_dirty = false;
	return factory.make_scroll(move(column));
}

bool Dev_Tools_Entity_List::is_dirty() const
{
	return m_dirty;
}
