#include "is_in_combat.hpp"
#include "utils/own_ptr.hpp"
#include "../conditions/is_in_combat.hpp"

namespace Condition_Factories {

Own_Ptr<Condition> Is_In_Combat::make_condition(Game_Facade& facade)
{
	return make_own_ptr<Conditions::Is_In_Combat>(facade);
}

}
