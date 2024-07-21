#include "add_to_party.hpp"
#include "utils/own_ptr.hpp"
#include "io/resource/character_profile_manager.hpp"
#include "../events/add_to_party.hpp"

namespace Event_Factories {

Add_To_Party::Add_To_Party(Character_Profile_Manager& mgr) :
	m_profile_manager{mgr}
{
	register_parameter("character", m_profile_filename);
}

Own_Ptr<Event> Add_To_Party::make_event(Game_Facade& facade)
{
	const Resource_Handle<Character_Profile> profile = m_profile_manager.get(m_profile_filename.value, false);
	return make_own_ptr<Events::Add_To_Party>(facade, profile);
}

}
