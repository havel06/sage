
#include "sequence/events/move_entity.hpp"
#include "utils/direction.hpp"
#include "map/entity.hpp"
#include "game/game_facade.hpp"
#include "utils/log.hpp"

namespace Events
{

Move_Entity::Move_Entity(Game_Facade& facade, String&& entity_name, Vec2i position) :
	Event{facade}
{
	m_entity_name = (String&&)entity_name;
	m_position = position;
}

void Move_Entity::update(float)
{
	m_game_facade.move_entity(m_entity_name, m_position);
}

bool Move_Entity::is_finished() const
{
	return m_game_facade.get_entity_position(m_entity_name) == m_position;
}

}
