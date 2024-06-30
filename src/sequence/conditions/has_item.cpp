#include "has_item.hpp"
#include "game/game_facade.hpp"

namespace Conditions
{

Has_Item::Has_Item(Game_Facade& facade, String&& id, int count) :
	Condition{facade}
{
	m_id = (String&&)id;
	m_count = count;
}

bool Has_Item::is_satisfied() const
{
	return m_game_facade.get_owned_item_count(m_id) >= m_count;
}


}
