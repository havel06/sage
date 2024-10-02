#include "has_item.hpp"
#include "utils/own_ptr.hpp"
#include "../conditions/has_item.hpp"

namespace Condition_Factories {

Has_Item::Has_Item()
{
	register_parameter("item", m_item);
	register_parameter("count", m_count);
}

Own_Ptr<Condition> Has_Item::make_condition(Game_Facade& facade)
{
	return make_own_ptr<Conditions::Has_Item>(facade, m_item.value, m_count.value);
}

}
