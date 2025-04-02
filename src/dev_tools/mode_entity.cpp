#include "mode_entity.hpp"
#include "dev_tools/entity_detail.hpp"
#include "graphics/editor_ui/factories/input_text.hpp"
#include "graphics/editor_ui/widget_factory2.hpp"
#include "map/map.hpp"
#include "utils/log.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"

Dev_Tools_Mode_Entity::Dev_Tools_Mode_Entity(Editor_UI::System& system, Map_Entities& entities) :
	m_gui{system},
	m_map_entities{entities}
{
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Mode_Entity::build()
{
	using namespace Editor_UI::Factories;

	m_dirty = false;

	auto detail = make_own_ptr<Dev_Tools_Entity_Detail>(m_gui);
	auto list = make_own_ptr<Dev_Tools_Entity_List>(
		m_map_entities, *detail, m_gui
	);

	return Column::make(Column::Padding::normal)
		->add(create_search_bar(*list))
		->add(Stateful::make(move(list)))
		->add(Stateful::make(move(detail)));
}

bool Dev_Tools_Mode_Entity::is_dirty() const
{
	return m_dirty;	
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Mode_Entity::create_search_bar(Dev_Tools_Entity_List& list)
{
	using namespace Editor_UI::Factories;

	auto callback = [&list](const String& text){
		list.set_searched_term(text);
	};

	return Input_Text::make(m_gui.get_font(), "Search")
		->on_edit(callback);
}
