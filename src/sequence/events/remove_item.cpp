#include "remove_item.hpp"
#include "game_facade.hpp"

namespace Events
{

Remove_Item::Remove_Item(String&& id, int count)
{
	m_id = (String&&)id;
	m_count = count;
}

void Remove_Item::update(Game_Facade& facade, float)
{
	m_activated = true;
	facade.remove_item(m_id, m_count);
}

bool Remove_Item::is_finished(Game_Facade&) const
{
	return m_activated;
}

void Remove_Item::reset()
{
	m_activated = false;
}

}
