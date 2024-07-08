#include "enable_player_actions.hpp"
#include "utils/own_ptr.hpp"
#include "../events/enable_player_actions.hpp"

namespace Event_Factories {

Own_Ptr<Event> Enable_Player_Actions::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Enable_Player_Actions>(facade);
}

}
