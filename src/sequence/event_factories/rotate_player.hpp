#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Rotate_Player final : public Event_Factory
{
public:
	Rotate_Player();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Direction_Event_Parameter m_direction;
};

}
