#pragma once

#include "utils/string.hpp"

class Resource_Manager;
class Game_Logic;

class Game_Facade
{
public:
	Game_Facade(Resource_Manager&, Game_Logic&);
	void set_current_map(const String& filename);
private:
	void spawn_player();

	Resource_Manager& m_res_manager;
	Game_Logic& m_logic;
};
