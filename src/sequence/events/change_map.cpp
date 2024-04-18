#include "change_map.hpp"
#include "game_facade.hpp"
#include "utils/log.hpp"

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

bool Change_Map::is_finished(Game_Facade&) const
{
	return m_activated;
}

void Change_Map::reset()
{
	m_activated = false;
}

}
