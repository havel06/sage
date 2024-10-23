#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Reset_Current_Unit_Sprite final : public Event_Factory
{
public:
	Reset_Current_Unit_Sprite() = default;
	Own_Ptr<Event> make_event(Game_Facade&) override;
};

}
