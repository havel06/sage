#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Disable_Player_Actions final : public Event_Factory
{
public:
	Own_Ptr<Event> make_event(Game_Facade&) override;
};

}
