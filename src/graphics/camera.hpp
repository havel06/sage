#pragma once

#include "utils/vec2.hpp"
#include <raylib/raylib.h>

class Game_Camera
{
public:
	Vec2f position;
	float zoom = 32;
	Camera2D to_ray_cam() const;
};
