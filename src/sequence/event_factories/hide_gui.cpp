#include "hide_gui.hpp"
#include "utils/own_ptr.hpp"
#include "../events/hide_gui.hpp"

namespace Event_Factories {

Own_Ptr<Event> Hide_GUI::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Hide_GUI>(facade);
}

}
