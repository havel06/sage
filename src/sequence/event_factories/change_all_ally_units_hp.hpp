#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Change_All_Ally_Units_HP final : public Event_Factory
{
public:
	Change_All_Ally_Units_HP();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Int_Event_Parameter m_amount;
};

}
