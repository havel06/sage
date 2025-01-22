#include "entity_detail.hpp"
#include "graphics/editor_ui/widgets/card_type.hpp"
#include "map/entity.hpp"
#include "map/map.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "graphics/editor_ui/widgets/card.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
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

Own_Ptr<Editor_UI::Widget> Dev_Tools_Entity_Detail::build()
{
	auto factory = m_system.get_widget_factory();

	if (!m_current_entity)
		return factory.make_text(""); // FIXME - dummy widget?

	auto card = factory.make_card(Editor_UI::Widgets::Card_Type::filled);
	
	card->column.add_child(factory.make_text(m_current_entity->name));

	auto x = factory.make_input_int("X", Editor_UI::Theme::SURFACE_CONTAINER_HIGHEST);
	auto y = factory.make_input_int("Y", Editor_UI::Theme::SURFACE_CONTAINER_HIGHEST);
	auto speed = factory.make_input_number("Move speed", Editor_UI::Theme::SURFACE_CONTAINER_HIGHEST);

	x->set_content(String::from_int(m_current_entity->position.x));
	y->set_content(String::from_int(m_current_entity->position.y));
	speed->set_content(String::from_float(m_current_entity->move_speed));

	x->on_edit = [this, x=x.get()](){
		if (x->is_valid())
			m_current_entity->position.x = atoi(x->get_content().data());
	};

	y->on_edit = [this, y=y.get()](){
		if (y->is_valid())
			m_current_entity->position.y = atoi(y->get_content().data());
	};

	speed->on_edit = [this, speed=speed.get()](){
		if (speed->is_valid())
			m_current_entity->move_speed = atof(speed->get_content().data());
	};

	card->column.add_child(move(x));
	card->column.add_child(move(y));
	card->column.add_child(move(speed));

	m_dirty = false;
	return card;
}

bool Dev_Tools_Entity_Detail::is_dirty() const
{
	return m_dirty;
}
