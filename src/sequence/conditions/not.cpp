#include "not.hpp"
#include "game/game_facade.hpp"
#include "sequence/condition.hpp"

namespace Conditions
{

Not::Not(Game_Facade& facade, Condition_Ptr&& condition) :
	Condition{facade}
{
	m_condition = (Condition_Ptr&&)condition;
}

bool Not::is_satisfied() const
{
	return !m_condition->is_satisfied();
}


}
