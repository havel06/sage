#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Add_Quest final : public Event_Factory
{
public:
	Add_Quest();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_id;
	String_Event_Parameter m_name;
	String_Event_Parameter m_description;
};

}
