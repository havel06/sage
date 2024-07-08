#include "echo.hpp"
#include "utils/own_ptr.hpp"
#include "../events/echo.hpp"

namespace Event_Factories {

Echo::Echo()
{
	register_parameter("message", m_message);
}

Own_Ptr<Event> Echo::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Echo>(facade, m_message.value);
}

}
