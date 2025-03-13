#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/string_parameter.hpp"
#include "templating/parameters/position_parameter.hpp"

namespace Event_Factories
{

class Teleport_Entity final : public Event_Factory
{
public:
	Teleport_Entity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_entity_name;
	Position_Parameter m_position;
};

}
