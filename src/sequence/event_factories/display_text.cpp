#include "display_text.hpp"
#include "utils/own_ptr.hpp"
#include "../events/display_text.hpp"

namespace Event_Factories {

Display_Text::Display_Text()
{
	register_parameter("message", m_message);
}

Own_Ptr<Event> Display_Text::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Display_Text>(facade, m_message.value);
}

}
