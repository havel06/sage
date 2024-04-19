#include "teleport_entity.hpp"
#include "game_facade.hpp"

namespace Events
{

Teleport_Entity::Teleport_Entity(Game_Facade& facade, String&& name, Vec2i position) :
	Event{facade}
{
	m_name = (String&&)name;
	m_position = position;
}

void Teleport_Entity::update(float)
{
	m_game_facade.teleport_entity(m_name, m_position);
	m_activated = true;
}

bool Teleport_Entity::is_finished() const
{
	return m_activated;
}

void Teleport_Entity::reset()
{
	m_activated = false;
}

}
