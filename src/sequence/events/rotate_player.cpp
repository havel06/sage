#include "rotate_player.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Rotate_Player::Rotate_Player(Game_Facade& facade, Direction direction) :
	Event(facade)
{
	m_direction = direction;
}

void Rotate_Player::update(float)
{
	m_game_facade.rotate_player(m_direction);
	m_activated = true;
}

void Rotate_Player::reset()
{
	m_activated = false;
}

bool Rotate_Player::is_finished() const
{
	return m_activated;
}


}
