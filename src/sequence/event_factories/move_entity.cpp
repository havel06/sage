#include "move_entity.hpp"
#include "utils/own_ptr.hpp"
#include "../events/move_entity.hpp"

namespace Event_Factories {

Move_Entity::Move_Entity()
{
	register_parameter("entity", m_entity_name);
	register_parameter("x", m_x);
	register_parameter("y", m_y);
}

Own_Ptr<Event> Move_Entity::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Move_Entity>(facade, m_entity_name.value, Vec2i{m_x.value, m_y.value});
}

}
