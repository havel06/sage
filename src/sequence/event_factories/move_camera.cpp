#include "move_camera.hpp"
#include "utils/own_ptr.hpp"
#include "../events/move_camera.hpp"

namespace Event_Factories {

Move_Camera::Move_Camera()
{
	register_parameter("position", m_position);
}

Own_Ptr<Event> Move_Camera::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Move_Camera>(facade, m_position.value);
}

}
