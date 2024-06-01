#pragma once

#include "game_logic.hpp"
#include "graphics/camera.hpp"
#include "graphics/camera_controller.hpp"
#include "graphics/combat_renderer.hpp"
#include "graphics/inventory_renderer.hpp"
#include "graphics/map_renderer.hpp"
#include "graphics/quest_log_renderer.hpp"
#include "graphics/text_box_renderer.hpp"
#include "io/resource/resource_system.hpp"
#include "io/sequence_loader.hpp"
#include "io/savegame/map_saveloader.hpp"
#include "io/savegame/sequence_saveloader.hpp"
#include "io/savegame/game_saveloader.hpp"
#include "map/map.hpp"
#include "music_player.hpp"
#include "sequence/sequence.hpp"
#include "combat_controller.hpp"

class Game
{
public:
	Game(const char* project_path);
	~Game();
	void draw_frame(float time_delta);
private:
	void process_normal_input();
	void process_combat_input();

	Game_Facade m_game_facade;
	Sequence_Loader m_sequence_loader;
	Resource_System m_resource_system;
	Game_Logic m_logic;
	Map_Renderer m_map_renderer;
	Music_Player m_music_player;
	Combat_Controller m_combat_controller;
	Map_Saveloader m_map_saveloader;
	Sequence_Saveloader m_sequence_saveloader;
	Game_Saveloader m_game_saveloader;

	// Rendering
	Game_Camera m_camera;
	Camera_Controller m_camera_controller;
	Text_Box_Renderer m_text_box_renderer;
	Inventory_Renderer m_inventory_renderer;
	Combat_Renderer m_combat_renderer;
	Quest_Log_Renderer m_quest_log_renderer;

	bool m_show_inventory = false;
	bool m_show_quest_log = false;
};
