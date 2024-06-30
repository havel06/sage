#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"
#include "battle_desc.hpp"

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

class Combat_Observer
{
public:
	virtual void on_hero_turn_begin() = 0;
};

// FIXME - refactor some parts into smaller classes
class Combat
{
public:
	Combat(Party& party);

	void add_observer(Combat_Observer&);
	void remove_observer(Combat_Observer&);

	void update();

	bool is_hero_turn() const { return m_is_hero_turn; }

	void start_battle(const Battle_Description&);
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

	Array<Combat_Observer*> m_observers;

	Array<Combat_Unit> m_heroes;
	Array<Combat_Unit> m_enemies;
	bool m_is_hero_turn = true;
	int m_current_hero_turn = 0;
	int m_current_enemy_turn = 0;
};
