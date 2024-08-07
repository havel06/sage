#include "teleport_camera_to_player.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Teleport_Camera_To_Player::Teleport_Camera_To_Player(Game_Facade& facade) :
	Event{facade}
{
}

void Teleport_Camera_To_Player::update(float)
{
	m_game_facade.teleport_camera_to_player();
	m_activated = true;
}

bool Teleport_Camera_To_Player::is_finished() const
{
	return m_activated;
}

void Teleport_Camera_To_Player::reset()
{
	m_activated = false;
}

}
