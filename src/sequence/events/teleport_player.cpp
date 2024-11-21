#include "teleport_player.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Teleport_Player::Teleport_Player(Game_Facade& facade, const Position& position) :
	Event{facade}
{
	m_position = position;
}

void Teleport_Player::update(float)
{
	m_game_facade.teleport_player(m_position);
	m_activated = true;
}

bool Teleport_Player::is_finished() const
{
	return m_activated;
}

void Teleport_Player::reset()
{
	m_activated = false;
}

}
