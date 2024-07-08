#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Rotate_Entity final : public Event_Factory
{
public:
	Rotate_Entity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_entity_name;
	Direction_Event_Parameter m_direction;
};

}
