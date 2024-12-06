#pragma once

#include "graphics/sprite.hpp"
#include "utils/array.hpp"
#include "character_profile.hpp"
#include "graphics/ui/size.hpp"
#include "combat_unit.hpp"

// fwd
class Sequence;

struct Battle_Unit_Placement
{
	UI::Size position_x;
	UI::Size position_y;
	UI::Size size_x;
	UI::Size size_y;
};

struct Battle_Units_Layout
{
	Array<Battle_Unit_Placement> heroes; // Placement of heroes
	Array<Battle_Unit_Placement> enemies; // Placement of enemies
};

struct Battle_Unit_Definition
{
	Resource_Handle<Character_Profile> character;
	int starting_hp;

	Battle_Unit_Definition(Resource_Handle<Character_Profile> profile, int hp) :
		character{profile},
		starting_hp{hp}
	{
	}

	Battle_Unit_Definition(Resource_Handle<Character_Profile> profile) :
		character{profile},
		starting_hp{profile.get().max_hp}
	{
	}
};

struct Battle_Description
{
	Optional<Array<Battle_Unit_Definition>> heroes; // If left empty, current party will be used
	Array<Battle_Unit_Definition> enemies;
	Resource_Handle<Sequence> win_sequence;
	Resource_Handle<Sequence> lose_sequence;
	Animated_Sprite background;
	Battle_Units_Layout units_layout;
	Combat_Unit_Side starting_side = Combat_Unit_Side::hero;
};
