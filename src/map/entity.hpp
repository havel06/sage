#pragma once

#include "graphics/sprite.hpp"
#include "utils/string.hpp"
#include "utils/vec2.hpp"

class Entity
{
public:
	String name;
	Vec2i position = {0, 0};
	Sprite sprite;
};
