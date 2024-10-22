#pragma once

#include "ability.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"
#include "graphics/animated_sprite.hpp"
#include "utils/vec2.hpp"

const float CHARACTER_DEFAULT_HP = 20;
const float CHARACTER_DEFAULT_SPEED = 5;

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

	float sprite_scale = 1;

	Vec2i size = {1, 1};

	Array<Ability> abilities;

	int max_hp = CHARACTER_DEFAULT_HP;
	float move_speed = CHARACTER_DEFAULT_SPEED;
};
