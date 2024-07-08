#include "teleport_player.hpp"
#include "utils/own_ptr.hpp"
#include "../events/teleport_player.hpp"

namespace Event_Factories {

Teleport_Player::Teleport_Player()
{
	register_parameter("x", m_x);
	register_parameter("y", m_y);
}

Own_Ptr<Event> Teleport_Player::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Teleport_Player>(facade, Vec2i{m_x.value, m_y.value});
}

}
