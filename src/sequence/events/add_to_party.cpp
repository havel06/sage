#include "add_to_party.hpp"
#include "game_facade.hpp"

namespace Events
{

Add_To_Party::Add_To_Party(Game_Facade& facade, const Character_Profile& profile) :
	Event{facade}
{
	m_profile = profile;
}

void Add_To_Party::update(float)
{
	m_game_facade.add_to_party(m_profile);
	m_activated = true;
}

bool Add_To_Party::is_finished() const
{
	return m_activated;
}

void Add_To_Party::reset()
{
	m_activated = false;
}

}
