#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Rotate_Player final : public Event_Factory
{
public:
	Rotate_Player();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Direction_Parameter m_direction;
};

}
