#pragma once

#include "ability.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"
#include "graphics/sprite.hpp"

struct Character_Profile
{
	String name;

	Sprite sprite_down;
	Sprite sprite_up;
	Sprite sprite_left;
	Sprite sprite_right;

	Array<Ability> abilities;

	int max_hp = 0;
};
