#pragma once

#include "utils/string.hpp"
#include "graphics/sprite.hpp"

struct Character_Profile
{
	String name;

	Sprite sprite_down;
	Sprite sprite_up;
	Sprite sprite_left;
	Sprite sprite_right;
};
