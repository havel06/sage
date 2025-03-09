#pragma once
#include "../event_factory.hpp"
#include "templating/parameter.hpp"

class Sound_Manager;

namespace Event_Factories
{

class Play_Sound final : public Event_Factory
{
public:
	Play_Sound(Sound_Manager&);
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Sound_Manager& m_sound_manager;

	String_Parameter m_sound_filename;
};

}
