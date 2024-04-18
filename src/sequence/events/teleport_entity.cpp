#include "teleport_entity.hpp"
#include "game_facade.hpp"

namespace Events
{

Teleport_Entity::Teleport_Entity(String&& name, Vec2i position)
{
	m_name = (String&&)name;
	m_position = position;
}

void Teleport_Entity::update(Game_Facade& facade, float)
{
	facade.teleport_entity(m_name, m_position);
	m_activated = true;
}

bool Teleport_Entity::is_finished(Game_Facade&) const
{
	return m_activated;
}

void Teleport_Entity::reset()
{
	m_activated = false;
}

}
