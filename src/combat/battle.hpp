#pragma once
#include "combat_unit.hpp"
#include "battle_desc.hpp"
#include "combat_observer.hpp"
#include "target_selection_type.hpp"

// fwd
class Party;
struct Item;

enum class Combat_State
{
	inactive,
	hero_selecting_ability,
	hero_selecting_enemy_target,
	hero_selecting_ally_target,
	hero_casting_ability,
	enemy_selecting_ability,
	enemy_selecting_target,
	enemy_casting_ability,
};

class Battle
{
public:
	Battle(const Battle_Description&, const Party&);

	Animated_Sprite get_background() const { return m_background; }
	const Battle_Units_Layout& get_units_layout() const { return m_units_layout; }
	Combat_State get_state() const { return m_state; }

	void update(); // Call every frame

	// Observer stuff
	void add_observer(Combat_Observer&);
	void remove_observer(Combat_Observer&);

	// Unit stuff
	int get_enemy_count() const;
	int get_hero_count() const;
	const Combat_Unit& get_hero(int index) const;
	const Combat_Unit& get_enemy(int index) const;
	const Combat_Unit& get_unit_on_turn() const;
	Combat_Unit& get_hero(int index);
	Combat_Unit& get_enemy(int index);
	Combat_Unit& get_unit_on_turn();

	// For controller
	void select_ability(int ability_index);
	void select_item(Item& item);
	void select_target(int target_index);

	// Interface for abilities
	void enter_target_selection(Target_Selection_Type);
	void change_target_hp(int amount);
	void change_current_unit_hp(int amount);
	void change_all_ally_units_hp(int amount);
	void change_all_enemy_units_hp(int amount);
	void set_current_unit_sprite(const Animated_Sprite& sprite);
	void reset_current_unit_sprite();
	void advance_turn();
private:
	bool is_hero_turn() const;
	void check_eliminated_units();
	bool has_player_won() const;
	bool has_player_lost() const;
	void reset_all_ability_sequences();

	Animated_Sprite m_background;
	Battle_Units_Layout m_units_layout;

	Optional<Resource_Handle<Sequence>> m_win_sequence;
	Optional<Resource_Handle<Sequence>> m_lose_sequence;

	Array<Combat_Unit> m_heroes;
	Array<Combat_Unit> m_enemies;
	int m_current_hero_turn = 0;
	int m_current_enemy_turn = 0;

	Combat_State m_state = Combat_State::inactive;
	int m_last_assigned_id = 0;

	Array<Combat_Observer*> m_observers;

	Combat_Unit* m_current_target = nullptr;
	Optional<Resource_Handle<Sequence>> m_current_casted_sequence; // Ability or item
};
