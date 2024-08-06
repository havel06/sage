#pragma once
#include "graphics/animated_sprite.hpp"

struct Tile
{
	Animated_Sprite sprite;
	bool passable = false;
};
