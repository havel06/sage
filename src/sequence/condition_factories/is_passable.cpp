#include "is_passable.hpp"
#include "utils/own_ptr.hpp"
#include "../conditions/is_passable.hpp"

namespace Condition_Factories {

Is_Passable::Is_Passable()
{
	register_parameter("position", m_position);
}

Own_Ptr<Condition> Is_Passable::make_condition(Game_Facade& facade)
{
	return make_own_ptr<Conditions::Is_Passable>(facade, m_position.value);
}

}
