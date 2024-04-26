#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"

class Party;

class Combat_Unit
{
public:
	Character_Profile character;
	int hp;

	Combat_Unit(Character_Profile);
};

class Combat
{
public:
	Combat(Party& party);

	void update();

	bool is_hero_turn() const { return m_is_hero_turn; }

	void start_battle(const Array<Character_Profile>& enemies);
	void use_ability(int ability_index, int target_index);

	int get_enemy_count() const;
	const Combat_Unit& get_hero(int index) const;
	const Combat_Unit& get_enemy(int index) const;
	const Combat_Unit& get_unit_on_turn() const;
	Combat_Unit& get_unit_on_turn();

private:
	void advance_turn();
	void check_eliminated_units();

	Party& m_party;

	Array<Combat_Unit> m_heroes;
	Array<Combat_Unit> m_enemies;
	bool m_is_hero_turn = true;
	int m_current_hero_turn;
	int m_current_enemy_turn;
};
