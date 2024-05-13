#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"

class Party;
class Sequence;

class Combat_Unit
{
public:
	Character_Profile character;
	int hp;

	Combat_Unit(Character_Profile);
};

enum class Combat_Result
{
	none,
	won,
	lost,
};

// FIXME - refactor some parts into smaller classes

class Combat
{
public:
	Combat(Party& party);

	void update();

	bool is_hero_turn() const { return m_is_hero_turn; }

	void start_battle(const Array<Character_Profile>& enemies, Sequence& win_sequence);
	void use_ability(int ability_index, int target_index);

	int get_enemy_count() const;
	int get_hero_count() const;
	const Combat_Unit& get_hero(int index) const;
	const Combat_Unit& get_enemy(int index) const;
	const Combat_Unit& get_unit_on_turn() const;
	Combat_Unit& get_unit_on_turn();

	Combat_Result get_current_result() const;

private:
	void advance_turn();
	void check_eliminated_units();
	bool has_player_won() const;
	bool has_player_lost() const;

	Party& m_party;
	Sequence* m_win_sequence;

	Array<Combat_Unit> m_heroes;
	Array<Combat_Unit> m_enemies;
	bool m_is_hero_turn = true;
	int m_current_hero_turn;
	int m_current_enemy_turn;
};
