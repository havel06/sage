#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"


class Combat
{
public:
	void add_enemy(const Character_Profile&);
	int get_enemy_count() const;
	const Character_Profile& get_enemy(int index) const;
private:
	Array<Character_Profile> m_enemies;
};
