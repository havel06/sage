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
	spawn_player();
	SG_INFO("Set current map to \"%s\"", filename.data());
}

void Game_Facade::spawn_player()
{
	Entity player;

	// FIXME - get from config
	player.sprite = Sprite{m_res_manager.get_texture("textures/sprites.png")};
	player.sprite.texture_clip.size = {16, 16};
	m_map.add_entity((Entity&&)player);
}
