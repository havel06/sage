#include "move_camera.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Move_Camera::Move_Camera(Game_Facade& game_facade, Vec2f position) :
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
	const float diff = (m_game_facade.get_camera_position() - m_position).manhattan();
	return diff < 0.01;
}

}
