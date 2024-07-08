#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Move_Entity final : public Event_Factory
{
public:
	Move_Entity();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_entity_name;
	Int_Event_Parameter m_x;
	Int_Event_Parameter m_y;
};

}
