#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Change_Current_Unit_Sprite final : public Event_Factory
{
public:
	Change_Current_Unit_Sprite();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Sprite_Event_Parameter m_sprite;
};

}
