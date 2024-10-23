#include "combat.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "combat/target_selection_type.hpp"
#include "combat_ai.hpp"
#include "graphics/animated_sprite.hpp"
#include "party.hpp"
#include "sequence/sequence.hpp"
#include "utils/log.hpp"
#include "item/item.hpp"

Combat_Unit::Combat_Unit(int id, Resource_Handle<Character_Profile> p, bool is_hero) :
	character{p},
	m_id{id},
	m_is_hero{is_hero}
{
	m_hp = character.get().max_hp;
}

bool Combat_Unit::operator==(const Combat_Unit& other) const
{
	return get_id() == other.get_id();
}

void Combat_Unit::change_hp(int amount)
{
	m_hp += amount;

	// Clamp to max hp
	const int max_hp = character.get().max_hp;
	if (m_hp > max_hp) {
		m_hp = max_hp;
	}
}

Combat::Combat(Party& party) :
	m_party{party}
{
}

void Combat::add_observer(Combat_Observer& observer)
{
	m_observers.push_back(&observer);
}

void Combat::remove_observer(Combat_Observer& observer)
{
	for (int i = 0; i < m_observers.size(); i++) {
		if (m_observers[i] == &observer) {
			m_observers.remove(i);
			return;
		}
	}
}

void Combat::start_battle(const Battle_Description& description)
{
	SG_DEBUG("Combat: Start battle");
	m_win_sequence = description.win_sequence;
	m_lose_sequence = description.lose_sequence;
	m_background = description.background;
	m_units_layout = description.units_layout;

	m_heroes.clear();
	m_enemies.clear();

	for (int i = 0; i < m_party.get_character_count(); i++) {
		m_heroes.push_back(Combat_Unit{m_last_assigned_id++, m_party.get_character(i), true});
	}

	for (Resource_Handle<Character_Profile> enemy : description.enemies) {
		m_enemies.push_back(Combat_Unit{m_last_assigned_id++, enemy, false});
	}

	m_state = Combat_State::hero_selecting_ability;
	m_current_hero_turn = 0;
	m_current_enemy_turn = 0;
	m_current_target = nullptr;
	m_current_casted_sequence = {};

	reset_all_ability_sequences();

	// Notify observers
	for (int i = 0; i < m_observers.size(); i++) {
		m_observers[i]->on_battle_begin();
		m_observers[i]->on_hero_ability_selecting_begin();
	}
}

void Combat::change_target_hp(int amount)
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

void Combat::change_current_unit_hp(int amount)
{
	get_unit_on_turn().change_hp(amount);

	// Notify observers
	for (Combat_Observer* observer : m_observers) {
		observer->on_unit_hp_change(get_unit_on_turn().get_id(), amount);
	}
}

void Combat::change_all_ally_units_hp(int amount)
{
	Array<Combat_Unit>& units = is_hero_turn() ? m_heroes : m_enemies;

	for (Combat_Unit& unit : units) {
		unit.change_hp(amount);

		// Notify observers
		for (Combat_Observer* observer : m_observers) {
			observer->on_unit_hp_change(unit.get_id(), amount);
		}
	}
}

void Combat::change_all_enemy_units_hp(int amount)
{
	Array<Combat_Unit>& units = is_hero_turn() ? m_enemies : m_heroes;

	for (Combat_Unit& unit : units) {
		unit.change_hp(amount);

		// Notify observers
		for (Combat_Observer* observer : m_observers) {
			observer->on_unit_hp_change(unit.get_id(), amount);
		}
	}
}

void Combat::enter_target_selection(Target_Selection_Type type)
{
	if (is_hero_turn()) {
		if (type == Target_Selection_Type::enemy)
			m_state = Combat_State::hero_selecting_enemy_target;
		else
			m_state = Combat_State::hero_selecting_ally_target;
	} else {
		// FIXME - ally selection for enemies
		m_state = Combat_State::enemy_selecting_target;
	}
}

int Combat::get_enemy_count() const
{
	return m_enemies.size();
}

int Combat::get_hero_count() const
{
	return m_heroes.size();
}

const Combat_Unit& Combat::get_hero(int index) const
{
	return m_heroes[index];
}

const Combat_Unit& Combat::get_enemy(int index) const
{
	return m_enemies[index];
}

bool Combat::is_hero_turn() const
{
	switch (m_state) {
		case Combat_State::hero_selecting_ability:
		case Combat_State::hero_selecting_enemy_target:
		case Combat_State::hero_selecting_ally_target:
		case Combat_State::hero_casting_ability:
			return true;
		case Combat_State::enemy_selecting_ability:
		case Combat_State::enemy_selecting_target:
		case Combat_State::enemy_casting_ability:
		case Combat_State::inactive:
			return false;
	}
}

const Combat_Unit& Combat::get_unit_on_turn() const
{
	if (is_hero_turn()) {
		return m_heroes[m_current_hero_turn];
	} else {
		return m_enemies[m_current_enemy_turn];
	}
}

Combat_Unit& Combat::get_unit_on_turn()
{
	if (is_hero_turn()) {
		return m_heroes[m_current_hero_turn];
	} else {
		return m_enemies[m_current_enemy_turn];
	}
}

void Combat::select_item(Item& item)
{
	SG_DEBUG("Combat: Selected item");

	assert(m_state == Combat_State::hero_selecting_ability ||
			m_state == Combat_State::enemy_selecting_ability);

	assert(item.assigned_sequence.has_value());
	item.assigned_sequence.value().get().try_activate();
	m_current_casted_sequence = item.assigned_sequence.value();

	m_state = is_hero_turn() ? Combat_State::hero_casting_ability : Combat_State::enemy_casting_ability;
}

void Combat::select_ability(int ability_index)
{
	SG_DEBUG("Combat: Selected ability");

	assert(m_state == Combat_State::hero_selecting_ability ||
			m_state == Combat_State::enemy_selecting_ability);

	Combat_Unit& unit = get_unit_on_turn();
	
	assert(ability_index >= 0);
	assert(ability_index < unit.character.get().abilities.size());
	Ability& ability = unit.character.get().abilities[ability_index];
	ability.sequence.get().try_activate();
	m_current_casted_sequence = ability.sequence;

	m_state = is_hero_turn() ? Combat_State::hero_casting_ability : Combat_State::enemy_casting_ability;
}

void Combat::select_target(int target_index)
{
	SG_DEBUG("Combat: Selected target");

	assert(target_index >= 0);

	switch (m_state) {
		case Combat_State::hero_selecting_enemy_target:
			assert(target_index < m_enemies.size());
			m_current_target = &m_enemies[target_index];
			break;
		case Combat_State::hero_selecting_ally_target:
			assert(target_index < m_heroes.size());
			m_current_target = &m_heroes[target_index];
			break;
		case Combat_State::enemy_selecting_target:
			assert(target_index < m_heroes.size());
			m_current_target = &m_heroes[target_index];
			break;
		default:
			assert(false);
	}

	m_state = is_hero_turn() ? Combat_State::hero_casting_ability : Combat_State::enemy_casting_ability;
}

void Combat::advance_turn()
{
	SG_DEBUG("Combat: advancing turn");
	m_current_target = nullptr;

	if (m_current_casted_sequence.has_value()) {
		m_current_casted_sequence.value().get().reset(); // Reset just in case
		m_current_casted_sequence = {};
	}

	if (is_hero_turn()) {
		m_state = Combat_State::enemy_selecting_ability;

		// Advance hero
		m_current_hero_turn++;

		// Overflow
		if (m_current_hero_turn >= m_heroes.size())
			m_current_hero_turn = 0;
	} else {
		m_state = Combat_State::hero_selecting_ability;

		// Advance enemy
		m_current_enemy_turn++;

		// Overflow
		if (m_current_enemy_turn >= m_enemies.size())
			m_current_enemy_turn = 0;

		// Notify observers
		for (int i = 0; i < m_observers.size(); i++) {
			m_observers[i]->on_hero_ability_selecting_begin();
		}
	}
}

void Combat::update()
{
	// Fix current unit index
	m_current_hero_turn %= m_heroes.size();
	m_current_enemy_turn %= m_enemies.size();

	// If there is only one enemy, we can skip target selection and select it
	if (m_state == Combat_State::hero_selecting_enemy_target && m_enemies.size() == 1) {
		select_target(0);
	}

	// If there is only one ally, we can skip target selection and select it
	if (m_state == Combat_State::hero_selecting_ally_target && m_heroes.size() == 1) {
		select_target(0);
	}
	
	// Advance state if current ability has finished
	if (m_state == Combat_State::hero_casting_ability ||
			m_state == Combat_State::enemy_casting_ability) {
		assert(m_current_casted_sequence.has_value());

		// We don't check for "finished", since the sequence can be repeatable
		if (!m_current_casted_sequence.value().get().is_active()) {
			m_current_casted_sequence.value().get().reset(); // Reset just in case
			m_current_casted_sequence = {};
			m_state = is_hero_turn() ? Combat_State::hero_selecting_ability : Combat_State::enemy_selecting_ability;

			// Notify observers
			for (int i = 0; i < m_observers.size(); i++) {
				m_observers[i]->on_hero_ability_selecting_begin();
			}
		} else {
			return;
		}
	}

	// Make enemy AI decision if needed
	Combat_AI ai(*this);
	if (m_state == Combat_State::enemy_selecting_ability) {
		select_ability(ai.decide_ability());
	} else if (m_state == Combat_State::enemy_selecting_target) {
		select_target(ai.decide_target(false)); // FIXME - enemies selecting ally targets
	}

	// Check eliminated units
	check_eliminated_units();

	// Check win condition
	if (has_player_won()) {
		SG_DEBUG("Battle has been won");
		m_win_sequence.value().get().try_activate();
		reset_all_ability_sequences();
		m_state = Combat_State::inactive;
	} else if (has_player_lost()) {
		SG_DEBUG("Battle has been lost");
		m_lose_sequence.value().get().try_activate();
		reset_all_ability_sequences();
		m_state = Combat_State::inactive;
	}
}

void Combat::reset_all_ability_sequences()
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

void Combat::check_eliminated_units()
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
}

Combat_Result Combat::get_current_result() const
{
	if (has_player_won())
		return Combat_Result::won;
	else if (has_player_lost())
		return Combat_Result::lost;
	else
		return Combat_Result::none;
}

bool Combat::has_player_won() const
{
	return m_enemies.empty();
}

bool Combat::has_player_lost() const
{
	return m_heroes.empty();
}

bool Combat::is_active() const
{
	return m_state != Combat_State::inactive;
}

void Combat::set_current_unit_sprite(const Animated_Sprite& sprite)
{
	get_unit_on_turn().custom_sprite = sprite;
}

void Combat::reset_current_unit_sprite()
{
	get_unit_on_turn().custom_sprite = Animated_Sprite{};
}
