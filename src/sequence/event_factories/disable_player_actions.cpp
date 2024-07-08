#include "disable_player_actions.hpp"
#include "utils/own_ptr.hpp"
#include "../events/disable_player_actions.hpp"

namespace Event_Factories {

Own_Ptr<Event> Disable_Player_Actions::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Disable_Player_Actions>(facade);
}

}
