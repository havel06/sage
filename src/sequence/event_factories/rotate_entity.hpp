#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/string_parameter.hpp"
#include "templating/parameters/direction_parameter.hpp"

namespace Event_Factories
{

class Rotate_Entity final : public Event_Factory
{
public:
	Rotate_Entity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_entity_name;
	Direction_Parameter m_direction;
};

}
