#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Move_Camera final : public Event_Factory
{
public:
	Move_Camera();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Position_Parameter m_position;
};

}
