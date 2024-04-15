#include "camera.hpp"
#include "raylib/raylib.h"

Camera2D Game_Camera::to_ray_cam() const
{
	float x = position.x * zoom - (float)GetScreenWidth() / 2;
	float y = position.y * zoom - (float)GetScreenHeight() / 2;

	return {{-x, -y}, {0, 0}, 0, zoom};
}
