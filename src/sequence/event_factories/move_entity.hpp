#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Move_Entity final : public Event_Factory
{
public:
	Move_Entity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_entity_name;
	Position_Parameter m_position;
};

}
