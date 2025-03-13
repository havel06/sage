#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/string_parameter.hpp"

namespace Event_Factories
{

class Remove_Sprite final : public Event_Factory
{
public:
	Remove_Sprite();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Parameter m_entity_name;
};

}
