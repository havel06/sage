#include "and.hpp"
#include "game/game_facade.hpp"
#include "sequence/condition.hpp"

namespace Conditions
{

And::And(Game_Facade& facade, Array<Condition_Ptr>&& conditions) :
	Condition{facade}
{
	m_conditions = move(conditions);
}

bool And::is_satisfied() const
{
	for (const Condition_Ptr& condition : m_conditions) {
		if (!condition->is_satisfied())
			return false;
	}

	return true;
}

}
