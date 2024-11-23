#include "is_passable.hpp"
#include "game/game_facade.hpp"
#include "sequence/condition.hpp"

namespace Conditions
{

Is_Passable::Is_Passable(Game_Facade& facade, const Position& position) :
	Condition{facade}
{
	m_position = position;
}

bool Is_Passable::is_satisfied() const
{
	return m_game_facade.is_passable(m_position);
}


}
