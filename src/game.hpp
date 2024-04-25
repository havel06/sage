#pragma once

#include "game_logic.hpp"
#include "graphics/camera.hpp"
#include "graphics/combat_renderer.hpp"
#include "graphics/inventory_renderer.hpp"
#include "graphics/map_renderer.hpp"
#include "graphics/quest_log_renderer.hpp"
#include "graphics/text_box_renderer.hpp"
#include "io/resource_manager.hpp"
#include "io/sequence_loader.hpp"
#include "map/map.hpp"
#include "music_player.hpp"
#include "sequence/sequence.hpp"

class Game
{
public:
	Game(const char* project_path);
	void draw_frame(float time_delta);
private:
	void process_normal_input();

	Game_Facade m_game_facade;
	Sequence_Loader m_sequence_loader;
	Resource_Manager m_res_manager;
	Game_Logic m_logic;
	Map_Renderer m_map_renderer;
	Text_Box_Renderer m_text_box_renderer;
	Inventory_Renderer m_inventory_renderer;
	Music_Player m_music_player;
	Game_Camera m_camera;
	Combat_Renderer m_combat_renderer;
	Quest_Log_Renderer m_quest_log_renderer;

	bool m_show_inventory = false;
	bool m_show_quest_log = false;
};
