#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/string_parameter.hpp"

namespace Event_Factories
{

class Finish_Quest final : public Event_Factory
{
public:
	Finish_Quest();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_id;
};

}
