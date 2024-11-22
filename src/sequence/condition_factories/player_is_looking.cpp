#include "player_is_looking.hpp"
#include "utils/own_ptr.hpp"
#include "../conditions/player_is_looking.hpp"

namespace Condition_Factories {

Player_Is_Looking::Player_Is_Looking()
{
	register_parameter("direction", m_direction);
}

Own_Ptr<Condition> Player_Is_Looking::make_condition(Game_Facade& facade)
{
	return make_own_ptr<Conditions::Player_Is_Looking>(facade, m_direction.value);
}

}
