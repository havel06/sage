#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

class Sequence_Manager;

namespace Event_Factories
{

class Activate_Sequence final : public Event_Factory
{
public:
	Activate_Sequence(Sequence_Manager&);
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Sequence_Manager& m_sequence_manager;
	String_Event_Parameter m_filename;
};

}
