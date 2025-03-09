#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

namespace Event_Factories
{

class Change_Sprite final : public Event_Factory
{
public:
	Change_Sprite();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_entity_name;
	Sprite_Parameter m_sprite;
};

}
