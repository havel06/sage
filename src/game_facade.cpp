#include "game_facade.hpp"
#include "io/resource_manager.hpp"
#include "utils/log.hpp"

Game_Facade::Game_Facade(Resource_Manager& res_mgr, Map& map) :
	m_res_manager{res_mgr},
	m_map{map}
{
}

void Game_Facade::set_current_map(const String& filename)
{
	m_map = m_res_manager.get_map(filename.data());
	SG_INFO("Set current map to \"%s\"", filename.data());
}
