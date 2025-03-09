#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Hide_GUI final : public Event_Factory
{
public:
	Own_Ptr<Event> make_event(Game_Facade&) override;
};

}
