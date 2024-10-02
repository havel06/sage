#include "not.hpp"
#include "utils/own_ptr.hpp"
#include "../conditions/not.hpp"

namespace Condition_Factories {

Not::Not()
{
	register_parameter("condition", m_condition);
}

Own_Ptr<Condition> Not::make_condition(Game_Facade& facade)
{
	return make_own_ptr<Conditions::Not>(facade, move(m_condition.value));
}

}
