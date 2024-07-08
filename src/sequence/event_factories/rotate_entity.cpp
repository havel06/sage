#include "rotate_entity.hpp"
#include "utils/own_ptr.hpp"
#include "../events/rotate_entity.hpp"

namespace Event_Factories {

Rotate_Entity::Rotate_Entity()
{
	register_parameter("entity", m_entity_name);
	register_parameter("direction", m_direction);
}

Own_Ptr<Event> Rotate_Entity::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Rotate_Entity>(facade, m_entity_name.value, m_direction.value);
}

}
