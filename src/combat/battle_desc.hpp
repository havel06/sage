#pragma once

#include "graphics/sprite.hpp"
#include "utils/array.hpp"
#include "character_profile.hpp"
#include "graphics/ui/size.hpp"

// fwd
class Sequence;

struct Battle_Unit_Placement
{
	UI::Size position_x;
	UI::Size position_y;
};

struct Battle_Units_Layout
{
	Array<Battle_Unit_Placement> hero_layout; // Placement of heroes
	Array<Battle_Unit_Placement> enemy_layout; // Placement of enemies
};

struct Battle_Description
{
	Array<Resource_Handle<Character_Profile>> enemies;
	Resource_Handle<Sequence> win_sequence;
	Resource_Handle<Sequence> lose_sequence;
	Animated_Sprite background;
	Battle_Units_Layout units_layout;
};
