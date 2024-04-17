#pragma once

#include "game_logic.hpp"
#include "graphics/camera.hpp"
#include "graphics/inventory_renderer.hpp"
#include "graphics/map_renderer.hpp"
#include "graphics/text_box_renderer.hpp"
#include "io/resource_manager.hpp"
#include "map/map.hpp"
#include "sequence/sequence.hpp"

class Game
{
public:
	Game(const char* project_path);
	void draw_frame(float time_delta);
private:
	void process_input();

	Resource_Manager m_res_manager;
	Game_Logic m_logic;
	Map_Renderer m_map_renderer;
	Text_Box_Renderer m_text_box_renderer;
	Inventory_Renderer m_inventory_renderer;
	Game_Camera m_camera;

	bool m_show_inventory = false;
};
