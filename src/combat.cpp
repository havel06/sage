#include "combat.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "combat_ai.hpp"
#include "party.hpp"
#include "utils/log.hpp"

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

int Combat::get_hero_count() const
{
	return m_heroes.size();
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

void Combat::use_ability(int ability_index, int target_index)
{
	SG_DEBUG("Use ability %d", ability_index);

	Combat_Unit& unit = get_unit_on_turn();
	
	assert(ability_index >= 0);
	assert(ability_index < unit.character.abilities.size());

	const Ability& ability = unit.character.abilities[ability_index];
	Combat_Unit& target = m_is_hero_turn ? m_enemies[target_index] : m_heroes[target_index];

	target.hp -= ability.damage;
	advance_turn();
}

void Combat::advance_turn()
{
	if (m_is_hero_turn) {
		// Advance hero
		m_current_hero_turn++;

		// Overflow
		if (m_current_hero_turn >= m_heroes.size())
			m_current_hero_turn = 0;
	} else {
		// Advance enemy
		m_current_enemy_turn++;

		// Overflow
		if (m_current_enemy_turn >= m_enemies.size())
			m_current_enemy_turn = 0;
	}

	m_is_hero_turn = !m_is_hero_turn;
}

void Combat::update()
{
	if (!m_is_hero_turn) {
		// Enemy turn
		Combat_AI ai(*this);
		auto decision = ai.make_decision();
		use_ability(decision.ability_index, decision.target_index);
	}

	check_eliminated_units();
}

void Combat::check_eliminated_units()
{
	auto check_array = [](Array<Combat_Unit>& units) {
		for (int i = 0; i < units.size(); i++) {
			if (units[i].hp <= 0) {
				units.remove(i);
				i--;
			}
		}
	};

	check_array(m_enemies);
	check_array(m_heroes);
}

Combat_Result Combat::get_current_result() const
{
	if (has_player_won())
		return Combat_Result::won;
	else if (has_player_lost())
		return Combat_Result::lost;
	else
		return Combat_Result::none;
}

bool Combat::has_player_won() const
{
	return m_enemies.empty();
}

bool Combat::has_player_lost() const
{
	return m_heroes.empty();
}
