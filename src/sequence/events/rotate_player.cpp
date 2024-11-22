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
}


bool Rotate_Player::is_finished() const
{
	return m_game_facade.get_player_direction() == m_direction;
}


}
