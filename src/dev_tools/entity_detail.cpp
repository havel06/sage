#include "entity_detail.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "map/entity.hpp"
#include "map/map.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/factories/card.hpp"
#include "graphics/editor_ui/factories/input_number.hpp"
#include "graphics/editor_ui/factories/input_integer.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include <cstdlib>

Dev_Tools_Entity_Detail::Dev_Tools_Entity_Detail(Editor_UI::System& system) :
	m_system{system}
{
}

void Dev_Tools_Entity_Detail::set_entity(Entity* entity)
{
	m_current_entity = entity;
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Entity_Detail::build()
{
	m_dirty = false;
	
	using namespace Editor_UI::Factories;

	if (!m_current_entity)
		return Dummy::make();

	return Card::make(Card::Type::filled,
		Column::make(Column::Padding::normal)
			->add(Text::make(m_system.get_font(), m_current_entity->name))
			->add(make_input_x())
			->add(make_input_y())
			->add(make_input_speed())
	);
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Entity_Detail::make_input_x()
{
	using namespace Editor_UI::Factories;

	auto callback = [this](bool valid, int value){
		if (valid)
			m_current_entity->position.x = value;
	};

	return Input_Integer::make(m_system.get_font(), "X")
		->on_enter(callback)
		->with_value(m_current_entity->position.x);
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Entity_Detail::make_input_y()
{
	using namespace Editor_UI::Factories;

	auto callback = [this](bool valid, int value){
		if (valid)
			m_current_entity->position.y = value;
	};

	return Input_Integer::make(m_system.get_font(), "Y")
		->on_enter(callback)
		->with_value(m_current_entity->position.y);
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Entity_Detail::make_input_speed()
{
	using namespace Editor_UI::Factories;

	auto callback = [this](bool valid, float value){
		if (valid)
			m_current_entity->move_speed = value;
	};

	return Input_Number::make(m_system.get_font(), "Move speed")
		->on_enter(callback)
		->with_value(m_current_entity->move_speed);
}

bool Dev_Tools_Entity_Detail::is_dirty() const
{
	return m_dirty;
}
