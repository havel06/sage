#include "combat.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "party.hpp"

Combat_Unit::Combat_Unit(Character_Profile p)
{
	character = p;
	hp = character.max_hp;
}

Combat::Combat(Party& party) :
	m_party{party}
{
}

void Combat::start_battle(const Array<Character_Profile>& enemies)
{
	m_heroes.clear();
	m_enemies.clear();

	for (int i = 0; i < m_party.get_character_count(); i++) {
		m_heroes.push_back(Combat_Unit{m_party.get_character(i)});
	}

	for (int i = 0; i < enemies.size(); i++) {
		m_enemies.push_back(Combat_Unit{enemies[i]});
	}
}

int Combat::get_enemy_count() const
{
	return m_enemies.size();
}

const Combat_Unit& Combat::get_hero(int index) const
{
	return m_heroes[index];
}

const Combat_Unit& Combat::get_enemy(int index) const
{
	return m_enemies[index];
}

const Combat_Unit& Combat::get_unit_on_turn() const
{
	if (m_is_hero_turn) {
		return m_heroes[m_current_hero_turn];
	} else {
		return m_enemies[m_current_enemy_turn];
	}
}

Combat_Unit& Combat::get_unit_on_turn()
{
	if (m_is_hero_turn) {
		return m_heroes[m_current_hero_turn];
	} else {
		return m_enemies[m_current_enemy_turn];
	}
}

void Combat::use_ability(int ability_index)
{
	assert(is_hero_turn());

	Combat_Unit& unit = get_unit_on_turn();
	
	assert(ability_index >= 0);
	assert(ability_index < unit.character.abilities.size());

	const Ability& ability = unit.character.abilities[ability_index];
	// FIXME
	(void)ability;
}
