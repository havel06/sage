#include "remove_item.hpp"
#include "utils/own_ptr.hpp"
#include "../events/remove_item.hpp"

namespace Event_Factories {

Remove_Item::Remove_Item()
{
	register_parameter("item", m_item_id);
	register_parameter("count", m_count);
}

Own_Ptr<Event> Remove_Item::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Remove_Item>(facade, m_item_id.value, m_count.value);
}

}
