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

void Camera_Controller::update(const Map& map, const Entity& player)
{
	const Vec2f new_pos = player.get_subgrid_position() + Vec2f{0.5, 0.5};

	if (is_player_out_of_camera(player.get_bounding_box())) {
		m_camera.position = new_pos;
		return;
	}

	const bool is_oob_horizontal = is_camera_out_of_bounds_horizontal(m_camera.position, m_camera.zoom, {map.get_width(), map.get_height()});
	const bool is_oob_vertical = is_camera_out_of_bounds_vertical(m_camera.position, m_camera.zoom, {map.get_width(), map.get_height()});
	const bool would_be_oob_horizontal = is_camera_out_of_bounds_horizontal(new_pos, m_camera.zoom, {map.get_width(), map.get_height()});
	const bool would_be_oob_vertical = is_camera_out_of_bounds_vertical(new_pos, m_camera.zoom, {map.get_width(), map.get_height()});

	if (is_oob_horizontal || !would_be_oob_horizontal) {
		m_camera.position.x = new_pos.x;
	}

	if (is_oob_vertical || !would_be_oob_vertical) {
		m_camera.position.y = new_pos.y;
	}
}

bool Camera_Controller::is_camera_out_of_bounds_horizontal(Vec2f position, float zoom, Vec2i map_size)
{
	const int screen_width = GetScreenWidth();

	const float camera_border_world_pos_left   = position.x - (float)screen_width  / 2 / zoom;
	const float camera_border_world_pos_right  = position.x + (float)screen_width  / 2 / zoom;

	if (camera_border_world_pos_left < 0) {
		return true;
	}

	if (camera_border_world_pos_right > map_size.x) {
		return true;
	}

	return false;
}

bool Camera_Controller::is_camera_out_of_bounds_vertical(Vec2f position, float zoom, Vec2i map_size)
{
	const int screen_height = GetScreenHeight();

	const float camera_border_world_pos_top    = position.y - (float)screen_height / 2 / zoom;
	const float camera_border_world_pos_bottom = position.y + (float)screen_height / 2 / zoom;

	if (camera_border_world_pos_top < 0) {
		return true;
	}

	if (camera_border_world_pos_bottom > map_size.y) {
		return true;
	}

	return false;
}

bool Camera_Controller::is_player_out_of_camera(Rectf player_rect)
{
	const int screen_width = GetScreenWidth();
	const int screen_height = GetScreenHeight();

	// FIXME - move this calculation to camera
	Rectf camera_rect = {
		.position = {
			.x = m_camera.position.x - (float)screen_width / 2 / m_camera.zoom,
			.y = m_camera.position.y - (float)screen_height / 2 / m_camera.zoom,
		},
		.size = {
			(float)screen_width / m_camera.zoom,
			(float)screen_height / m_camera.zoom
		}
	};

	return !camera_rect.overlaps(player_rect);
}
