#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

class Character_Profile_Manager;

namespace Event_Factories
{

class Add_To_Party final : public Event_Factory
{
public:
	Add_To_Party(Character_Profile_Manager&);
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Character_Profile_Manager& m_profile_manager;
	String_Event_Parameter m_profile_filename;
};

}
