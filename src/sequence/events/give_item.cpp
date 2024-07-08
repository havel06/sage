#include "give_item.hpp"
#include "game/game_facade.hpp"

namespace Events
{

Give_Item::Give_Item(Game_Facade& facade, const String& id, int count) :
	Event{facade}
{
	m_id = id;
	m_count = count;
}

void Give_Item::update(float)
{
	m_activated = true;
	m_game_facade.give_item(m_id, m_count);
}

bool Give_Item::is_finished() const
{
	return m_activated;
}

void Give_Item::reset()
{
	m_activated = false;
}

}
