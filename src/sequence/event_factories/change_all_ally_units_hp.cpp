#include "change_all_ally_units_hp.hpp"
#include "utils/own_ptr.hpp"
#include "../events/change_all_ally_units_hp.hpp"

namespace Event_Factories {

Change_All_Ally_Units_HP::Change_All_Ally_Units_HP()
{
	register_parameter("amount", m_amount);
}

Own_Ptr<Event> Change_All_Ally_Units_HP::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Change_All_Ally_Units_HP>(facade, m_amount.value);
}

}
