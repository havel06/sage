#pragma once

#include "utils/string.hpp"

class Map;
class Resource_Manager;

class Game_Facade
{
public:
	Game_Facade(Resource_Manager&, Map&);
	void set_current_map(const String& filename);
private:
	void spawn_player();

	Resource_Manager& m_res_manager;
	Map& m_map;
};
