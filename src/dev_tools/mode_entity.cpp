#include "mode_entity.hpp"
#include "dev_tools/entity_detail.hpp"
#include "dev_tools/entity_list.hpp"
#include "graphics/editor_ui/factories/input_text.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "map/map.hpp"
#include "utils/log.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"

Dev_Tools_Mode_Entity::Dev_Tools_Mode_Entity(Map_Entities& entities) :
	m_map_entities{entities}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Mode_Entity::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	m_dirty = false;

	auto detail = make_own_ptr<Dev_Tools_Entity_Detail>();
	auto list = make_own_ptr<Dev_Tools_Entity_List>(m_map_entities, *detail, m_searched_term);

	return Column::make(Column::Padding::normal)
		->add(create_search_bar(theme))
		->add(Stateful::make(move(list)))
		->add(Stateful::make(move(detail)));
}

bool Dev_Tools_Mode_Entity::is_dirty() const
{
	return m_dirty;	
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Mode_Entity::create_search_bar(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [this](const String& text){
		m_searched_term = text;
		m_dirty = true;
	};

	return Input_Text::make(m_input_state, theme.font, "Search")
		->on_edit(callback);
}
