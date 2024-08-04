#include "camera_controller.hpp"
#include "camera.hpp"
#include "../map/map.hpp"
#include "../map/entity.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"

Camera_Controller::Camera_Controller(Game_Camera& cam) :
	m_camera{cam}
{
}

Vec2f Camera_Controller::get_camera_position() const
{
	return m_camera.position;
}

void Camera_Controller::update(const Map& map, const Entity& player, float dt)
{
	if (m_mode == Camera_Controller_Mode::follow_player)
		update_follow_player(map, player);
	else
		update_fixed(dt);
}

void Camera_Controller::update_follow_player(const Map& map, const Entity& player)
{
	m_camera.position = player.get_subgrid_position() + Vec2f{0.5, 1};
	fix_camera_out_of_bounds({map.get_width(), map.get_height()});
}

void Camera_Controller::update_fixed(float dt)
{
	const float move_speed = 5;
	Vec2f position_diff = m_fixed_target - m_camera.position;
	m_camera.position += position_diff * dt * move_speed;
}

void Camera_Controller::set_fixed_target(Vec2f pos)
{
	m_mode = Camera_Controller_Mode::fixed;
	m_fixed_target = pos;
}

void Camera_Controller::fix_camera_out_of_bounds(Vec2i map_size)
{
	fix_camera_out_of_bounds_horizontal(map_size);
	fix_camera_out_of_bounds_vertical(map_size);
}

void Camera_Controller::fix_camera_out_of_bounds_horizontal(Vec2i map_size)
{
	if (get_camera_view_world_width() > map_size.x) {
		// Room smaller than camera
		return;
	}

	const int screen_width = GetScreenWidth();

	const float camera_border_world_pos_left   = m_camera.position.x - (float)screen_width  / 2 / m_camera.zoom;
	const float camera_border_world_pos_right  = m_camera.position.x + (float)screen_width  / 2 / m_camera.zoom;

	if (camera_border_world_pos_left < 0) {
		m_camera.position.x += -(camera_border_world_pos_left);
	} else if (camera_border_world_pos_right > map_size.x) {
		m_camera.position.x -= camera_border_world_pos_right - map_size.x;
	}
}

void Camera_Controller::fix_camera_out_of_bounds_vertical(Vec2i map_size)
{
	if (get_camera_view_world_height() > map_size.x) {
		// Room smaller than camera
		return;
	}

	const int screen_height = GetScreenHeight();

	const float camera_border_world_pos_top    = m_camera.position.y - (float)screen_height / 2 / m_camera.zoom;
	const float camera_border_world_pos_bottom = m_camera.position.y + (float)screen_height / 2 / m_camera.zoom;

	if (camera_border_world_pos_top < 0) {
		m_camera.position.y += -(camera_border_world_pos_top);
	} else if (camera_border_world_pos_bottom > map_size.y) {
		m_camera.position.y -= camera_border_world_pos_bottom - map_size.y;
	}
}

void Camera_Controller::set_zoom(int amount)
{
	m_camera.zoom = amount;
}

int Camera_Controller::get_camera_view_world_width()
{
	return GetScreenWidth() / m_camera.zoom;
}

int Camera_Controller::get_camera_view_world_height()
{
	return GetScreenHeight() / m_camera.zoom;
}
