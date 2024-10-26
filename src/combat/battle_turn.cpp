#include "battle_turn.hpp"
#include "combat_unit.hpp"
#include "combat_observer.hpp"
#include "item/item.hpp"
#include "combat_ai.hpp"
#include "utils/log.hpp"

Battle_Turn::Battle_Turn(Array<Combat_Unit>& allies, Array<Combat_Unit>& enemies, int unit_on_turn) :
	m_allies{allies},
	m_enemies{enemies},
	m_unit_on_turn{unit_on_turn}
{
}

void Battle_Turn::update()
{
	// If there is only one enemy, we can skip target selection and select it
	if (m_state == Battle_Turn_State::selecting_enemy_target && m_enemies.size() == 1) {
		select_target(0);
	}

	// If there is only one ally, we can skip target selection and select it
	if (m_state == Battle_Turn_State::selecting_ally_target && m_enemies.size() == 1) {
		select_target(0);
	}

	// Advance state if current ability has finished
	if (m_state == Battle_Turn_State::casting_ability) {
		assert(m_current_casted_sequence.has_value());

		// We don't check for "finished", since the sequence can be repeatable
		if (!m_current_casted_sequence.value().get().is_active()) {
			m_current_casted_sequence.value().get().reset(); // Reset
			if (m_ready_to_advance) {
				m_state = Battle_Turn_State::finished;
			} else {
				m_state = Battle_Turn_State::selecting_action;
				// Notify observers
				for (int i = 0; i < m_observers.size(); i++) {
					m_observers[i]->on_hero_ability_selecting_begin();
				}
			}

		} else {
			return;
		}
	}

	// Make enemy AI decision if needed
	if (get_unit_on_turn().get_side() == Combat_Unit_Side::enemy) {
		Combat_AI ai(*this);
		if (m_state == Battle_Turn_State::selecting_action) {
			select_ability(ai.decide_ability());
		} else if (m_state == Battle_Turn_State::selecting_enemy_target) {
			select_target(ai.decide_enemy_target());
		} else if (m_state == Battle_Turn_State::selecting_ally_target) {
			select_target(ai.decide_ally_target());
		}
	}
}

void Battle_Turn::add_observer(Combat_Observer& observer)
{
	m_observers.push_back(&observer);
}

void Battle_Turn::remove_observer(Combat_Observer& observer)
{
	for (int i = 0; i < m_observers.size(); i++) {
		if (m_observers[i] == &observer) {
			m_observers.remove(i);
			return;
		}
	}
}

void Battle_Turn::change_target_hp(int amount)
{
	if (!m_current_target) {
		SG_ERROR("Could not change target hp: no target selected.");
		return;
	}

	m_current_target->change_hp(amount);

	// Notify observers
	for (Combat_Observer* observer : m_observers) {
		observer->on_unit_hp_change(m_current_target->get_id(), amount);
	}
}

void Battle_Turn::change_current_unit_hp(int amount)
{
	m_allies[m_unit_on_turn].change_hp(amount);

	// Notify observers
	for (Combat_Observer* observer : m_observers) {
		observer->on_unit_hp_change(m_allies[m_unit_on_turn].get_id(), amount);
	}
}

void Battle_Turn::change_all_ally_units_hp(int amount)
{
	for (Combat_Unit& unit : m_allies) {
		unit.change_hp(amount);

		// Notify observers
		for (Combat_Observer* observer : m_observers) {
			observer->on_unit_hp_change(unit.get_id(), amount);
		}
	}
}

void Battle_Turn::change_all_enemy_units_hp(int amount)
{
	for (Combat_Unit& unit : m_enemies) {
		unit.change_hp(amount);

		// Notify observers
		for (Combat_Observer* observer : m_observers) {
			observer->on_unit_hp_change(unit.get_id(), amount);
		}
	}
}

void Battle_Turn::enter_target_selection(Target_Selection_Type type)
{
	if (m_state != Battle_Turn_State::casting_ability) {
		SG_ERROR("Cannot enter target selection.");
		return;
	}

	if (type == Target_Selection_Type::enemy)
		m_state = Battle_Turn_State::selecting_enemy_target;
	else
		m_state = Battle_Turn_State::selecting_ally_target;
}

void Battle_Turn::select_item(Item& item)
{
	assert(m_state == Battle_Turn_State::selecting_action);

	assert(item.assigned_sequence.has_value());
	item.assigned_sequence.value().get().try_activate();
	m_current_casted_sequence = item.assigned_sequence.value();

	m_state = Battle_Turn_State::casting_ability;

	SG_DEBUG("Combat: Selected item");
}

void Battle_Turn::select_ability(int ability_index)
{
	assert(m_state == Battle_Turn_State::selecting_action);

	assert(ability_index >= 0);
	assert(ability_index < m_allies[m_unit_on_turn].character.get().abilities.size());
	Ability& ability = m_allies[m_unit_on_turn].character.get().abilities[ability_index];
	ability.sequence.get().try_activate();
	m_current_casted_sequence = ability.sequence;

	m_state = Battle_Turn_State::casting_ability;

	SG_DEBUG("Combat: Selected ability");
}

void Battle_Turn::select_target(int target_index)
{
	SG_DEBUG("Combat: Selected target");

	assert(target_index >= 0);

	switch (m_state) {
		case Battle_Turn_State::selecting_enemy_target:
			assert(target_index < m_enemies.size());
			m_current_target = &m_enemies[target_index];
			break;
		case Battle_Turn_State::selecting_ally_target:
			assert(target_index < m_allies.size());
			m_current_target = &m_allies[target_index];
			break;
		default:
			assert(false);
	}

	m_state = Battle_Turn_State::casting_ability;
}

void Battle_Turn::set_current_unit_sprite(const Animated_Sprite& sprite)
{
	m_allies[m_unit_on_turn].custom_sprite = sprite;
}

void Battle_Turn::reset_current_unit_sprite()
{
	m_allies[m_unit_on_turn].custom_sprite = Animated_Sprite{};
}

void Battle_Turn::advance_turn()
{
	m_ready_to_advance = true;
}
