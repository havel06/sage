#pragma once

#include "utils/rect.hpp"
#include "utils/vec2.hpp"
class Game_Camera;
class Entity;
class Map;

enum class Camera_Controller_Mode
{
	follow_player,
	fixed,
};

class Camera_Controller
{
public:
	Camera_Controller(Game_Camera&);

	Vec2f get_camera_position() const;

	void update(const Map& map, const Entity& player, float dt); // Call every frame
	void set_zoom(int amount);
	void set_fixed_target(Vec2f pos);
private:
	void update_follow_player(const Map&, const Entity& player);
	void update_fixed(float dt);
	
	void fix_camera_out_of_bounds(Vec2i map_size);
	void fix_camera_out_of_bounds_horizontal(Vec2i map_size);
	void fix_camera_out_of_bounds_vertical(Vec2i map_size);
	int get_camera_view_world_width();
	int get_camera_view_world_height();

	Game_Camera& m_camera;
	Camera_Controller_Mode m_mode = Camera_Controller_Mode::follow_player;
	Vec2f m_fixed_target = {0, 0};
};
