#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"
#include "battle_desc.hpp"

class Party;
class Sequence;

// FIXME - separate some parts of this file

class Combat_Unit
{
public:
	Resource_Handle<Character_Profile> character;
	int hp;

	Combat_Unit(Resource_Handle<Character_Profile>);
};

enum class Combat_Result
{
	none,
	won,
	lost,
};

// FIXME - consider removing, only use combat state information in Combat_Controller
class Combat_Observer
{
public:
	virtual void on_hero_turn_begin() = 0;
};

enum class Combat_State
{
	hero_selecting_ability,
	hero_selecting_target,
	hero_casting_ability,
	enemy_selecting_ability,
	enemy_selecting_target,
	enemy_casting_ability,
};

// FIXME - refactor some parts into smaller classes
class Combat
{
public:
	Combat(Party& party);

	// Observer stuff
	void add_observer(Combat_Observer&);
	void remove_observer(Combat_Observer&);

	// Call every frame
	void update();

	Combat_State get_state() const { return m_state; }

	void start_battle(const Battle_Description&);

	// For controller
	void select_ability(int ability_index);
	void select_target(int target_index);

	// Interface for abilities
	void enter_target_selection();
	void change_target_hp(int amount);

	// Unit stuff
	int get_enemy_count() const;
	int get_hero_count() const;
	const Combat_Unit& get_hero(int index) const;
	const Combat_Unit& get_enemy(int index) const;
	const Combat_Unit& get_unit_on_turn() const;
	Combat_Unit& get_unit_on_turn();

	Combat_Result get_current_result() const;

private:
	bool is_hero_turn() const;
	void advance_turn();
	void check_eliminated_units();
	bool has_player_won() const;
	bool has_player_lost() const;

	Party& m_party;

	Combat_State m_state = Combat_State::hero_selecting_ability;

	Array<Combat_Observer*> m_observers;
	Optional<Resource_Handle<Sequence>> m_win_sequence;
	Optional<Resource_Handle<Sequence>> m_lose_sequence;

	Array<Combat_Unit> m_heroes;
	Array<Combat_Unit> m_enemies;
	int m_current_hero_turn = 0;
	int m_current_enemy_turn = 0;

	Combat_Unit* m_current_target = nullptr;
	Ability* m_current_casted_ability = nullptr;
};
