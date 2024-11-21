#include "move_camera.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Move_Camera::Move_Camera(Game_Facade& game_facade, const Position& position) :
	Event{game_facade}
{
	m_position = position;
}

void Move_Camera::update(float)
{
	m_game_facade.move_camera(m_position);
}

bool Move_Camera::is_finished() const
{
	const Vec2f current_pos = m_game_facade.get_camera_position();
	const Vec2f target_pos = m_game_facade.resolve_position(m_position);

	const float diff = (target_pos - current_pos).manhattan();

	return diff < 0.01;
}

}
