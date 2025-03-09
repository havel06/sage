#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Delay final : public Event_Factory
{
public:
	Delay();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Float_Parameter m_seconds;
};

}
