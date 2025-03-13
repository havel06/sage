#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/position_parameter.hpp"

namespace Event_Factories
{

class Teleport_Player final : public Event_Factory
{
public:
	Teleport_Player();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Position_Parameter m_position;
};

}
