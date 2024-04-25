#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"

class Party;

class Combat
{
public:
	Combat(Party& party);
	void add_enemy(const Character_Profile&);
	int get_enemy_count() const;
	const Character_Profile& get_enemy(int index) const;
	const Character_Profile& get_character_on_turn() const;
	bool is_hero_turn() const { return m_is_hero_turn; }
private:
	Party& m_party;

	Array<Character_Profile> m_enemies;
	bool m_is_hero_turn = true;
	int m_current_hero_turn;
	int m_current_enemy_turn;
};
