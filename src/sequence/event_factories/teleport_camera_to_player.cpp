#include "teleport_camera_to_player.hpp"
#include "utils/own_ptr.hpp"
#include "../events/teleport_camera_to_player.hpp"

namespace Event_Factories {

Own_Ptr<Event> Teleport_Camera_To_Player::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Teleport_Camera_To_Player>(facade);
}

}
