#pragma once

#include "utils/vec2.hpp"
#include "utils/rect.hpp"
#include <raylib/raylib.h>

class Game_Camera
{
public:
	Vec2f position;
	float zoom = 32;
	Rectf get_frustrum() const;
	Camera2D to_ray_cam() const;
	Vec2i unproject(Vec2f coord) const;
};
