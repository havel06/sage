#include "camera.hpp"
#include "game/game.hpp"
#include "raylib/raylib.h"

Camera2D Game_Camera::to_ray_cam() const
{
	float x = position.x * zoom - (float)GetScreenWidth() / 2;
	float y = position.y * zoom - (float)GetScreenHeight() / 2;

	return {{-x, -y}, {0, 0}, 0, zoom};
}

Rectf Game_Camera::get_frustrum() const
{
	return Rectf{
		.position = Vec2f{
			.x = position.x - (float)GetScreenWidth() / 2 / zoom,
			.y = position.y - (float)GetScreenHeight() / 2 / zoom
		},
		.size = Vec2f{
			.x = (float)GetScreenWidth() / zoom,
			.y = (float)GetScreenHeight() / zoom
		}
	};
}

Vec2i Game_Camera::unproject(Vec2f coord) const
{
	const int x = GetScreenWidth() / 2 + (int)((coord.x - position.x) * zoom);
	const int y = GetScreenHeight() / 2 + (int)((coord.y - position.y) * zoom);
	return {x, y};
}
