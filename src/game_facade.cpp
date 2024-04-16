#include "game_facade.hpp"
#include "io/resource_manager.hpp"
#include "utils/log.hpp"
#include "game_logic.hpp"

Game_Facade::Game_Facade(Resource_Manager& res_mgr, Game_Logic& logic) :
	m_res_manager{res_mgr},
	m_logic{logic}
{
}

void Game_Facade::set_current_map(const String& filename)
{
	m_logic.map = m_res_manager.get_map(filename.data());
	spawn_player();
	SG_INFO("Set current map to \"%s\"", filename.data());
}

void Game_Facade::spawn_player()
{
	// TODO - maybe this should happen in game_logic
	Entity player;

	// FIXME - get from config
	player.name = "Player";
	player.sprite = Sprite{m_res_manager.get_texture("textures/sprites.png")};
	player.sprite.texture_clip.size = {16, 16};
	m_logic.map.add_entity((Entity&&)player);
}

void Game_Facade::teleport_player(Vec2i position)
{
	m_logic.get_player().position = position;
}
