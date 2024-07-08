#include "delay.hpp"
#include "utils/own_ptr.hpp"
#include "../events/delay.hpp"

namespace Event_Factories {

Delay::Delay()
{
	register_parameter("seconds", m_seconds);
}

Own_Ptr<Event> Delay::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Delay>(facade, m_seconds.value);
}

}
