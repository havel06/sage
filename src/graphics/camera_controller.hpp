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
	void set_zoom(int amount);
private:
	void fix_camera_out_of_bounds(Vec2i map_size);
	void fix_camera_out_of_bounds_horizontal(Vec2i map_size);
	void fix_camera_out_of_bounds_vertical(Vec2i map_size);
	int get_camera_view_world_width();
	int get_camera_view_world_height();

	Game_Camera& m_camera;
};
