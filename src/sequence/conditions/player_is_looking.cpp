#include "player_is_looking.hpp"
#include "game/game_facade.hpp"
#include "sequence/condition.hpp"

namespace Conditions
{

Player_Is_Looking::Player_Is_Looking(Game_Facade& facade, Direction direction) :
	Condition{facade}
{
	m_direction = direction;
}

bool Player_Is_Looking::is_satisfied() const
{
	return m_game_facade.get_player_direction() == m_direction;
}


}
