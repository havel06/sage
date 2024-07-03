#pragma once

#include "ability.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"
#include "graphics/animated_sprite.hpp"
#include "utils/vec2.hpp"

struct Character_Profile
{
	String name;
	String filename;

	Animated_Sprite sprite_down;
	Animated_Sprite sprite_up;
	Animated_Sprite sprite_left;
	Animated_Sprite sprite_right;

	Animated_Sprite sprite_move_down;
	Animated_Sprite sprite_move_up;
	Animated_Sprite sprite_move_left;
	Animated_Sprite sprite_move_right;

	Vec2f size = {1, 1};

	Array<Ability> abilities;

	int max_hp = 0;
	float move_speed = 5;
};
