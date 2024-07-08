#include "change_map.hpp"
#include "utils/own_ptr.hpp"
#include "../events/change_map.hpp"

namespace Event_Factories {

Change_Map::Change_Map()
{
	register_parameter("map", m_map_filename);
}

Own_Ptr<Event> Change_Map::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Change_Map>(facade, m_map_filename.value);
}

}
