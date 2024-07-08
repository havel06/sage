#include "change_map.hpp"
#include "game/game_facade.hpp"
#include "utils/log.hpp"

namespace Events
{

Change_Map::Change_Map(Game_Facade& facade, const String& new_map) :
	Event{facade}
{
	m_new_map = new_map;
}

void Change_Map::update(float)
{
	m_game_facade.set_current_map(m_new_map);
	m_activated = true;
}

bool Change_Map::is_finished() const
{
	return m_activated;
}

void Change_Map::reset()
{
	m_activated = false;
}

}
