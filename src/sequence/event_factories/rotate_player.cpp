#include "rotate_player.hpp"
#include "utils/own_ptr.hpp"
#include "../events/rotate_player.hpp"

namespace Event_Factories {

Rotate_Player::Rotate_Player()
{
	register_parameter("direction", m_direction);
}

Own_Ptr<Event> Rotate_Player::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Rotate_Player>(facade, m_direction.value);
}

}
