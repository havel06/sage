#include "battle.hpp"
#include "combat/battle_desc.hpp"
#include "combat/battle_turn.hpp"
#include "combat/combat_observer.hpp"
#include "combat/combat_unit.hpp"
#include "party.hpp"
#include "item/item.hpp"

void Battle::add_observer(Combat_Observer& observer)
{
	m_observers.push_back(&observer);
	m_current_turn->add_observer(observer);
}

void Battle::remove_observer(Combat_Observer& observer)
{
	for (int i = 0; i < m_observers.size(); i++) {
		if (m_observers[i] == &observer) {
			m_observers.remove(i);
			return;
		}
	}

	m_current_turn->remove_observer(observer);
}

Battle::Battle(const Battle_Description& description, const Party& party) :
	m_description{description}
{
	m_heroes.clear();
	m_enemies.clear();

	for (int i = 0; i < party.get_character_count(); i++) {
		m_heroes.push_back(Combat_Unit{m_last_assigned_id++, party.get_character(i), Combat_Unit_Side::hero});
	}

	for (Resource_Handle<Character_Profile> enemy : description.enemies) {
		m_enemies.push_back(Combat_Unit{m_last_assigned_id++, enemy, Combat_Unit_Side::enemy});
	}

	m_current_hero_turn = 0;
	m_current_enemy_turn = 0;
	reset_all_ability_sequences(); // TODO - this might be unnecessarry

	m_current_turn = make_own_ptr<Battle_Turn>(m_heroes, m_enemies, m_current_hero_turn);
}

int Battle::get_enemy_count() const
{
	return m_enemies.size();
}

int Battle::get_hero_count() const
{
	return m_heroes.size();
}

const Combat_Unit& Battle::get_hero(int index) const
{
	return m_heroes[index];
}

const Combat_Unit& Battle::get_enemy(int index) const
{
	return m_enemies[index];
}

Combat_Unit& Battle::get_hero(int index)
{
	return m_heroes[index];
}

Combat_Unit& Battle::get_enemy(int index)
{
	return m_enemies[index];
}

const Combat_Unit& Battle::get_unit_on_turn() const
{
	if (m_current_side == Combat_Unit_Side::hero) {
		return m_heroes[m_current_hero_turn];
	} else {
		return m_enemies[m_current_enemy_turn];
	}
}

Combat_Unit& Battle::get_unit_on_turn()
{
	return const_cast<Combat_Unit&>(static_cast<const Battle*>(this)->get_unit_on_turn());
}

bool Battle::has_player_won() const
{
	return m_enemies.empty();
}

bool Battle::has_player_lost() const
{
	return m_heroes.empty();
}

void Battle::advance_turn()
{
	SG_DEBUG("Combat: advancing turn");

	if (m_current_side == Combat_Unit_Side::hero) {
		// Advance hero
		m_current_hero_turn++;
		m_current_side = Combat_Unit_Side::enemy;
		m_current_turn = make_own_ptr<Battle_Turn>(m_enemies, m_heroes, m_current_enemy_turn);

		// Add observers
		for (Combat_Observer* observer : m_observers) {
			m_current_turn->add_observer(*observer);
		}
	} else {
		// Advance enemy
		m_current_enemy_turn++;
		m_current_side = Combat_Unit_Side::hero;
		m_current_turn = make_own_ptr<Battle_Turn>(m_heroes, m_enemies, m_current_hero_turn);

		// Add observers
		for (Combat_Observer* observer : m_observers) {
			m_current_turn->add_observer(*observer);
		}

		// Notify observers
		for (int i = 0; i < m_observers.size(); i++) {
			m_observers[i]->on_hero_ability_selecting_begin();
		}
	}

	fix_current_turn_indices();
}

void Battle::update()
{
	if (m_finished)
		return;

	m_current_turn->update();

	if (m_current_turn->is_finished()) {
		// Check eliminated units
		check_eliminated_units();

		// Check win condition
		if (has_player_won()) {
			SG_DEBUG("Battle has been won");
			m_description.win_sequence.get().try_activate();
			reset_all_ability_sequences();
			m_finished = true;
		} else if (has_player_lost()) {
			SG_DEBUG("Battle has been lost");
			m_description.lose_sequence.get().try_activate();
			reset_all_ability_sequences();
			m_finished = true;
		} else {
			advance_turn();
		}
	}
}

void Battle::reset_all_ability_sequences()
{
	auto reset_abilities_for_unit = [&](Combat_Unit& unit) {
		for (Ability& ability : unit.character.get().abilities) {
			ability.sequence.get().reset();
		}
	};

	for (Combat_Unit& unit : m_heroes) {
		reset_abilities_for_unit(unit);
	}
	
	for (Combat_Unit& unit : m_enemies) {
		reset_abilities_for_unit(unit);
	}
}

void Battle::check_eliminated_units()
{
	auto check_array = [](Array<Combat_Unit>& units) {
		for (int i = 0; i < units.size(); i++) {
			if (units[i].get_hp() <= 0) {
				units.remove(i);
				i--;
			}
		}
	};

	check_array(m_enemies);
	check_array(m_heroes);

	fix_current_turn_indices();
}

void Battle::fix_current_turn_indices()
{
	if (m_heroes.size() > 0)
		m_current_hero_turn %= m_heroes.size();

	if (m_enemies.size() > 0)
		m_current_enemy_turn %= m_enemies.size();
}
