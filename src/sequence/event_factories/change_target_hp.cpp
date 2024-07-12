#include "change_target_hp.hpp"
#include "utils/own_ptr.hpp"
#include "../events/change_target_hp.hpp"

namespace Event_Factories {

Change_Target_HP::Change_Target_HP()
{
	register_parameter("amount", m_amount);
}

Own_Ptr<Event> Change_Target_HP::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Change_Target_HP>(facade, m_amount.value);
}

}
