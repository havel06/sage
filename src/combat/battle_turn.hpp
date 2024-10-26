#pragma once

#include "target_selection_type.hpp"
#include "io/resource/resource_handle.hpp"
#include "utils/optional.hpp"
#include "utils/array.hpp"

// fwd
class Combat_Unit;
struct Item;
class Animated_Sprite;
class Sequence;
class Combat_Observer;

enum class Battle_Turn_State
{
	selecting_action,
	casting_ability,
	selecting_ally_target,
	selecting_enemy_target,
	finished
};

class Battle_Turn
{
public:
	Battle_Turn(Array<Combat_Unit>& allies, Array<Combat_Unit>& enemies, int unit_on_turn);

	void update(); // Call every frame
	Battle_Turn_State get_state() const { return m_state; }
	bool is_finished() const { return m_state == Battle_Turn_State::finished; }

	// Unit stuff
	const Combat_Unit& get_unit_on_turn() const { return m_allies[m_unit_on_turn]; }
	int get_enemy_count() const { return m_enemies.size(); }
	int get_ally_count() const { return m_allies.size(); }
	const Combat_Unit& get_ally(int index) const { return m_allies[index]; }
	const Combat_Unit& get_enemy(int index) const { return m_enemies[index]; }

	// Observer stuff
	void add_observer(Combat_Observer&);
	void remove_observer(Combat_Observer&);

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
	Array<Combat_Unit>& m_allies;
	Array<Combat_Unit>& m_enemies;
	int m_unit_on_turn = 0;

	Battle_Turn_State m_state = Battle_Turn_State::selecting_action;
	Combat_Unit* m_current_target = nullptr;
	bool m_ready_to_advance = false;
	Optional<Resource_Handle<Sequence>> m_current_casted_sequence;

	Array<Combat_Observer*> m_observers;
};
