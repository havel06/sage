#pragma once
#include "../event_factory.hpp"
#include "../event_parameter.hpp"

class Sequence_Manager;
class Character_Profile_Manager;

namespace Event_Factories
{

class Enter_Combat final : public Event_Factory
{
public:
	Enter_Combat(Sequence_Manager&, Character_Profile_Manager&);
	Own_Ptr<Event> make_event(Game_Facade&) override;
private:
	Sequence_Manager& m_sequence_manager;
	Character_Profile_Manager& m_character_profile_manager;

	String_Array_Event_Parameter m_enemy_filenames;
	String_Event_Parameter m_win_sequence_filename;
	String_Event_Parameter m_lose_sequence_filename;
};

}
