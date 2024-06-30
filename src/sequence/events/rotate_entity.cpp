#include "rotate_entity.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Rotate_Entity::Rotate_Entity(Game_Facade& facade, String&& entity_name, Direction direction) :
	Event(facade)
{
	m_entity_name = (String&&)entity_name;
	m_direction = direction;
}

void Rotate_Entity::update(float)
{
	m_game_facade.rotate_entity(m_entity_name, m_direction);
}

bool Rotate_Entity::is_finished() const
{
	return m_game_facade.get_entity_direction(m_entity_name) == m_direction;
}


}
