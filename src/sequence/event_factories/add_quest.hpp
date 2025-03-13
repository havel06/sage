#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/string_parameter.hpp"

namespace Event_Factories
{

class Add_Quest final : public Event_Factory
{
public:
	Add_Quest();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_id;
	String_Parameter m_name;
	String_Parameter m_description;
};

}
