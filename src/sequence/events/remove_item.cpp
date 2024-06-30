#include "remove_item.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Remove_Item::Remove_Item(Game_Facade& facade, String&& id, int count) :
	Event{facade}
{
	m_id = (String&&)id;
	m_count = count;
}

void Remove_Item::update(float)
{
	m_activated = true;
	m_game_facade.remove_item(m_id, m_count);
}

bool Remove_Item::is_finished() const
{
	return m_activated;
}

void Remove_Item::reset()
{
	m_activated = false;
}

}
