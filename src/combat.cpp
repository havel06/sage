#include "combat.hpp"

void Combat::add_enemy(const Character_Profile& enemy)
{
	m_enemies.push_back(enemy);
}

int Combat::get_enemy_count() const
{
	return m_enemies.size();
}

const Character_Profile& Combat::get_enemy(int index) const
{
	return m_enemies[index];
}
