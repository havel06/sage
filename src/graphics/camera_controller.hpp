#pragma once

#include "utils/rect.hpp"
#include "utils/vec2.hpp"
class Game_Camera;
class Entity;
class Map;

class Camera_Controller
{
public:
	Camera_Controller(Game_Camera&);
	void update(const Map& map, const Entity& player);
private:
	bool is_camera_out_of_bounds_horizontal(Vec2f position, float zoom, Vec2i map_size);
	bool is_camera_out_of_bounds_vertical(Vec2f position, float zoom, Vec2i map_size);
	bool is_player_out_of_camera(Rectf player_rect);

	Game_Camera& m_camera;
};
