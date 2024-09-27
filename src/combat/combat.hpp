#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"
#include "battle_desc.hpp"

// fwd
class Party;
class Sequence;
struct Item;

// FIXME - separate some parts of this file

class Combat_Unit
{
public:
	Resource_Handle<Character_Profile> character;
	int get_id() const { return m_id; }
	int get_hp() const { return m_hp; }
	bool is_hero() const { return m_is_hero; }
	bool is_enemy() const { return !m_is_hero; }
	void change_hp(int amount);

	Combat_Unit(int id, Resource_Handle<Character_Profile>, bool is_hero);
private:
	int m_id;
	int m_hp;
	bool m_is_hero;
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
	virtual void on_battle_begin() = 0;
	virtual void on_hero_ability_selecting_begin() = 0;
};

enum class Combat_State
{
	inactive,
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
	bool is_active() const;

	void start_battle(const Battle_Description&);
	Animated_Sprite get_background() const { return m_background; }

	// For controller
	void select_ability(int ability_index);
	void select_item(Item& item);
	void select_target(int target_index);

	// Interface for abilities
	void enter_target_selection();
	void change_target_hp(int amount);
	void change_current_unit_hp(int amount);
	void change_all_enemy_units_hp(int amount);
	void advance_turn();

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
	void check_eliminated_units();
	bool has_player_won() const;
	bool has_player_lost() const;
	void reset_all_ability_sequences();

	Party& m_party;

	Combat_State m_state = Combat_State::inactive;
	int m_last_assigned_id = 0;

	Array<Combat_Observer*> m_observers;
	Optional<Resource_Handle<Sequence>> m_win_sequence;
	Optional<Resource_Handle<Sequence>> m_lose_sequence;
	Animated_Sprite m_background;

	Array<Combat_Unit> m_heroes;
	Array<Combat_Unit> m_enemies;
	int m_current_hero_turn = 0;
	int m_current_enemy_turn = 0;

	Combat_Unit* m_current_target = nullptr;
	Optional<Resource_Handle<Sequence>> m_current_casted_sequence; // Ability or item
};
