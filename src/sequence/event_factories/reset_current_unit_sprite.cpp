#include "reset_current_unit_sprite.hpp"
#include "utils/own_ptr.hpp"
#include "../events/reset_current_unit_sprite.hpp"

namespace Event_Factories {

Own_Ptr<Event> Reset_Current_Unit_Sprite::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Reset_Current_Unit_Sprite>(facade);
}

}
