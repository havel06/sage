#include "combat_unit.hpp"
#include "battle_desc.hpp"

Combat_Unit::Combat_Unit(int id, const Battle_Unit_Definition& def, Combat_Unit_Side side) :
	character{def.character},
	m_id{id},
	m_side{side}
{
	m_hp = def.starting_hp;
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
