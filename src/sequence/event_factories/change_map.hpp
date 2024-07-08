#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

namespace Event_Factories
{

class Change_Map final : public Event_Factory
{
public:
	Change_Map();
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	String_Event_Parameter m_map_filename;
};

}