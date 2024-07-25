#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class End_Turn final : public Event_Factory
{
public:
	End_Turn();
	Own_Ptr<Event> make_event(Game_Facade&) override;
};

}
