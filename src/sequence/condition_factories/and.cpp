#include "and.hpp"
#include "utils/own_ptr.hpp"
#include "../conditions/and.hpp"

namespace Condition_Factories {

And::And()
{
	register_parameter("conditions", m_conditions);
}

Own_Ptr<Condition> And::make_condition(Game_Facade& facade)
{
	return make_own_ptr<Conditions::And>(facade, move(m_conditions.value));
}

}
