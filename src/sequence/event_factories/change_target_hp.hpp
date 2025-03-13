#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/int_parameter.hpp"

namespace Event_Factories
{

class Change_Target_HP final : public Event_Factory
{
public:
	Change_Target_HP();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Int_Parameter m_amount;
};

}
