#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Teleport_Entity final : public Event_Factory
{
public:
	Teleport_Entity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_entity_name;
	Position_Event_Parameter m_position;
};

}
