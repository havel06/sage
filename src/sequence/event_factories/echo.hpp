#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Echo final : public Event_Factory
{
public:
	Echo();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_message;
};

}
