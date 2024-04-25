#include "combat.hpp"
#include "party.hpp"

Combat::Combat(Party& party) :
	m_party{party}
{
}

void Combat::add_enemy(const Character_Profile& enemy)
{
	m_enemies.push_back(enemy);
}

int Combat::get_enemy_count() const
{
	return m_enemies.size();
}

const Character_Profile& Combat::get_enemy(int index) const
{
	return m_enemies[index];
}

const Character_Profile& Combat::get_character_on_turn() const
{
	if (m_is_hero_turn) {
		return m_party.get_character(m_current_hero_turn);
	} else {
		return m_enemies[m_current_enemy_turn];
	}
}
