#include "change_current_unit_hp.hpp"
#include "utils/own_ptr.hpp"
#include "../events/change_current_unit_hp.hpp"

namespace Event_Factories {

Change_Current_Unit_HP::Change_Current_Unit_HP()
{
	register_parameter("amount", m_amount);
}

Own_Ptr<Event> Change_Current_Unit_HP::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Change_Current_Unit_HP>(facade, m_amount.value);
}

}
