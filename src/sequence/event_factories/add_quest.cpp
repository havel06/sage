#include "add_quest.hpp"
#include "utils/own_ptr.hpp"
#include "../events/add_quest.hpp"

namespace Event_Factories {

Add_Quest::Add_Quest()
{
	register_parameter("id", m_id);
	register_parameter("name", m_name);
	register_parameter("description", m_description);
}

Own_Ptr<Event> Add_Quest::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Add_Quest>(facade, m_id.value, m_name.value, m_description.value);
}

}
