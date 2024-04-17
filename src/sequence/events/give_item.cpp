#include "give_item.hpp"
#include "game_facade.hpp"

namespace Events
{

Give_Item::Give_Item(String&& id, int count)
{
	m_id = (String&&)id;
	m_count = count;
}

void Give_Item::update(Game_Facade& facade, float)
{
	m_activated = true;
	facade.give_item(m_id, m_count);
}

bool Give_Item::is_finished(Game_Facade&) const
{
	return m_activated;
}

void Give_Item::reset()
{
	m_activated = false;
}

}
