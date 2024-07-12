#include "select_target.hpp"
#include "utils/own_ptr.hpp"
#include "../events/select_target.hpp"

namespace Event_Factories {

Select_Target::Select_Target()
{
	register_parameter("target_type", m_selection_type);
}

Own_Ptr<Event> Select_Target::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Select_Target>(facade, m_selection_type.value);
}

}
