#include "entity_detail.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "map/entity.hpp"
#include "map/map.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/factories/card.hpp"
#include "graphics/editor_ui/factories/input_number.hpp"
#include "graphics/editor_ui/factories/input_integer.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include <cstdlib>

void Dev_Tools_Entity_Detail::set_entity(Entity* entity)
{
	m_current_entity = entity;
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Entity_Detail::build(const Editor_UI::Theme& theme)
{
	m_dirty = false;
	
	using namespace Editor_UI::Factories;

	if (!m_current_entity)
		return Dummy::make();

	return Card::make(Card::Type::filled,
		Column::make(Column::Padding::normal)
			->add(Text::make(theme.font, m_current_entity->name))
			->add(make_input_x(theme))
			->add(make_input_y(theme))
			->add(make_input_speed(theme))
	);
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Entity_Detail::make_input_x(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [this](bool valid, int value){
		if (valid)
			m_current_entity->position.x = value;
	};

	return Input_Integer::make(m_state_x, theme.font, "X")
		->on_enter(callback)
		->with_value(m_current_entity->position.x);
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Entity_Detail::make_input_y(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [this](bool valid, int value){
		if (valid)
			m_current_entity->position.y = value;
	};

	return Input_Integer::make(m_state_y, theme.font, "Y")
		->on_enter(callback)
		->with_value(m_current_entity->position.y);
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Entity_Detail::make_input_speed(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [this](bool valid, float value){
		if (valid)
			m_current_entity->move_speed = value;
	};

	return Input_Number::make(m_state_speed, theme.font, "Move speed")
		->on_enter(callback)
		->with_value(m_current_entity->move_speed);
}

bool Dev_Tools_Entity_Detail::is_dirty() const
{
	return m_dirty;
}
