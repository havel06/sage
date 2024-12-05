#pragma once
#include "graphics/animated_sprite.hpp"
#include "character_profile.hpp"

struct Battle_Unit_Definition;

enum class Combat_Unit_Side
{
	hero,
	enemy
};


class Combat_Unit
{
public:
	Resource_Handle<Character_Profile> character;
	Animated_Sprite custom_sprite; // For ability animations etc

	Combat_Unit(int id, const Battle_Unit_Definition&, Combat_Unit_Side side);
	bool operator==(const Combat_Unit& other) const;

	int get_id() const { return m_id; }
	Combat_Unit_Side get_side() const { return m_side; }
	int get_hp() const { return m_hp; }
	void change_hp(int amount);
private:
	int m_id;
	int m_hp;
	Combat_Unit_Side m_side;
};
