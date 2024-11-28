#pragma once
#include "combat_unit.hpp"
#include "battle_desc.hpp"
#include "combat_observer.hpp"
#include "io/resource/resource_handle.hpp"
#include "target_selection_type.hpp"
#include "battle_turn.hpp"

// fwd
class Party;
struct Item;

class Battle
{
public:
	Battle(const Battle_Description&, const Party&);
	Battle(Battle&&) = delete;
	Battle(const Battle&) = delete;

	const Battle_Description& get_description() const { return m_description; }
	Combat_Unit_Side get_current_side() const { return m_current_side; }
	bool has_finished() const { return m_finished; }
	Battle_Turn& get_current_turn() { return *m_current_turn; }
	const Battle_Turn& get_current_turn() const { return *m_current_turn; }

	void update(); // Call every frame

	// Observer stuff
	// FIXME - consider using something like a mediator pattern
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
private:
	void check_eliminated_units();
	bool has_player_won() const;
	bool has_player_lost() const;
	void reset_all_ability_sequences();
	void advance_turn();
	void fix_current_turn_indices();

	Battle_Description m_description;

	Array<Combat_Unit> m_heroes;
	Array<Combat_Unit> m_enemies;
	int m_current_hero_turn = 0;
	int m_current_enemy_turn = 0;
	Own_Ptr<Battle_Turn> m_current_turn;

	Combat_Unit_Side m_current_side = Combat_Unit_Side::hero;
	bool m_finished = false;
	int m_last_assigned_id = 0;

	Array<Combat_Observer*> m_observers;
};
