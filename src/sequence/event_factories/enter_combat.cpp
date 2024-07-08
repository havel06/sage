#include "enter_combat.hpp"
#include "combat/battle_desc.hpp"
#include "utils/own_ptr.hpp"
#include "utils/move.hpp"
#include "io/resource/character_profile_manager.hpp"
#include "io/resource/sequence_manager.hpp"
#include "../events/enter_combat.hpp"

namespace Event_Factories {

Enter_Combat::Enter_Combat(Sequence_Manager& seq_mgr, Character_Profile_Manager& profile_mgr) :
	m_sequence_manager{seq_mgr},
	m_character_profile_manager{profile_mgr}
{
	register_parameter("enemies", m_enemy_filenames);
	register_parameter("win_sequence", m_win_sequence_filename);
	register_parameter("lose_sequence", m_lose_sequence_filename);
}

Own_Ptr<Event> Enter_Combat::make_event(Game_Facade& facade)
{
	Array<Character_Profile> enemy_profiles;
	for (const String& filename : m_enemy_filenames.value) {
		enemy_profiles.push_back(m_character_profile_manager.get(filename, false));
	}

	Sequence& win_sequence = m_sequence_manager.get(m_win_sequence_filename.value, false);
	Sequence& lose_sequence = m_sequence_manager.get(m_lose_sequence_filename.value, false);

	Battle_Description description {
		.enemies = move(enemy_profiles),
		.win_sequence = win_sequence,
		.lose_sequence = lose_sequence
	};

	return make_own_ptr<Events::Enter_Combat>(facade, move(description));
}

}
