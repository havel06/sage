#include "give_item.hpp"
#include "utils/own_ptr.hpp"
#include "../events/give_item.hpp"

namespace Event_Factories {

Give_Item::Give_Item()
{
	register_parameter("item", m_item_id);
	register_parameter("count", m_count);
}

Own_Ptr<Event> Give_Item::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Give_Item>(facade, m_item_id.value, m_count.value);
}

}
