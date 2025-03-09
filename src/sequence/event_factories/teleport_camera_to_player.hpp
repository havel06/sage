#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Teleport_Camera_To_Player final : public Event_Factory
{
public:
	Own_Ptr<Event> make_event(Game_Facade&) override;
};

}
