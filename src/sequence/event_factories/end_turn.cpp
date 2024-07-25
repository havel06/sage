#include "end_turn.hpp"
#include "utils/own_ptr.hpp"
#include "../events/end_turn.hpp"

namespace Event_Factories {

End_Turn::End_Turn()
{
}

Own_Ptr<Event> End_Turn::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::End_Turn>(facade);
}

}
