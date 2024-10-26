#include "combat.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "combat/battle.hpp"
#include "combat/battle_desc.hpp"
#include "combat/combat_unit.hpp"
#include "combat/target_selection_type.hpp"
#include "combat_ai.hpp"
#include "graphics/animated_sprite.hpp"
#include "party.hpp"
#include "sequence/sequence.hpp"
#include "utils/log.hpp"
#include "item/item.hpp"
#include "utils/optional.hpp"


Combat::Combat(const Party& party) :
	m_party{party}
{
}

void Combat::update()
{
	assert(m_battle);

	m_battle->update();

	if (m_battle->has_finished()) {
		// Battle has ended
		m_battle = Own_Ptr<Battle>{};
	}
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

const Battle& Combat::get_battle() const
{
	assert(m_battle);
	return *m_battle;
}

Battle& Combat::get_battle()
{
	assert(m_battle);
	return *m_battle;
}

void Combat::start_battle(const Battle_Description& description)
{
	SG_DEBUG("Combat: Start battle");
	m_battle = make_own_ptr<Battle>(description, m_party);

	// Notify observers
	for (Combat_Observer* observer : m_observers) {
		m_battle->add_observer(*observer);
	}

	for (Combat_Observer* observer : m_observers) {
		observer->on_battle_begin();
		observer->on_hero_ability_selecting_begin();
	}
}

bool Combat::is_active() const
{
	return m_battle;
}
