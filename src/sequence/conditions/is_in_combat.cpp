#include "is_in_combat.hpp"
#include "game/game_facade.hpp"
#include "sequence/condition.hpp"

namespace Conditions
{

Is_In_Combat::Is_In_Combat(Game_Facade& facade) :
	Condition{facade}
{
}

bool Is_In_Combat::is_satisfied() const
{
	return m_game_facade.is_in_combat();
}


}
