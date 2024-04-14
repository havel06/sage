#include "change_map.hpp"
#include "game_facade.hpp"

namespace Events
{

Change_Map::Change_Map(String&& new_map)
{
	m_new_map = (String&&)new_map;
}

void Change_Map::update(Game_Facade& facade, float)
{
	facade.set_current_map(m_new_map);
	m_activated = true;
}

bool Change_Map::is_finished() const
{
	return m_activated;
}

}
