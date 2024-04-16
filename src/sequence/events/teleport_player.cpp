#include "teleport_player.hpp"
#include "game_facade.hpp"

namespace Events
{

Teleport_Player::Teleport_Player(Vec2i position)
{
	m_position = position;
}

void Teleport_Player::update(Game_Facade& facade, float)
{
	facade.teleport_player(m_position);
	m_activated = true;
}

bool Teleport_Player::is_finished() const
{
	return m_activated;
}

}
