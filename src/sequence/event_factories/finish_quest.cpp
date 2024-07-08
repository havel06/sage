#include "finish_quest.hpp"
#include "utils/own_ptr.hpp"
#include "../events/finish_quest.hpp"

namespace Event_Factories {

Finish_Quest::Finish_Quest()
{
	register_parameter("id", m_id);
}

Own_Ptr<Event> Finish_Quest::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Finish_Quest>(facade, m_id.value);
}

}
